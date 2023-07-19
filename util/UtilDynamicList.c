#pragma once
#include "../tier0/logging/Logging.h"
#include "Util.h"
#include "UtilDynamicList.h"

#define EUPHORIA_DYNAMIC_LIST_REALLOC_MAX_MULTIPLY 50000
#define EUPHORIA_DYNAMIC_LIST_DELETE_MARKER 0x6666666666666666 // very hard/impossible to get allocated to this memory address (always 0x00000...on windows, test on linux)

// Creates a new list.
DynamicList* DynamicList_new(uint32_t capacity)
{
	// Capacity must be at least zero.
	assert(capacity > 0);

	// don't allocate under 10 items just for the sake of not endlessly reallocating on small lists
	if (capacity < 10) capacity = 10;

	// malloc list object
	DynamicList* newList = (DynamicList*)malloc(sizeof(DynamicList));

	assert(newList != NULL);

	memset(newList, 0x00, sizeof(newList));

	newList->capacity = capacity;

	newList->items = malloc(sizeof(uintptr_t) * capacity);

	assert(newList->items != NULL);

	memset(newList->items, 0x00, sizeof(uintptr_t) * capacity);

	return newList;
}

// Adds the item item to list list.
// Returns a TRUE if the item was successfully added.
// Returns a FALSE if the item was unsuccessfully added.
bool DynamicList_AddItem(DynamicList* list, void* item)
{
	assert(list != NULL);
	assert(item != NULL);
	// TODO: find first free item

	// transparent resize
	// don't duplicate if we are above some arbitrary number for memory concerns

	if (list->count >= list->capacity)
	{
		uint32_t newCapacity = list->capacity * 2;

		if (list->capacity > EUPHORIA_DYNAMIC_LIST_REALLOC_MAX_MULTIPLY) newCapacity = list->capacity * 1.1;

		DynamicList_Resize(list, newCapacity);
	}

	// get ram position of final item
	uintptr_t finalPosition = ((uintptr_t)list->items) + (sizeof(uintptr_t) * list->count);

	memcpy((void*)finalPosition, &item, sizeof(uintptr_t));

	list->count++;

	return true;
}

// Obtains the item with index index in list list.
// Returns a pointer to the pointer containing the item item if it is in the list.
// Otherwise returns a NULL pointer.
void** DynamicList_GetItemIndex(DynamicList* list, uint32_t index)
{
	assert(list != NULL);
	assert(index >= 0 
		&& index < list->capacity);

	void** ptrLocation = (void*)((uintptr_t)list->items + (sizeof(uintptr_t) * index));

	if (*ptrLocation == EUPHORIA_DYNAMIC_LIST_DELETE_MARKER) return NULL;
	return ptrLocation;
}

// Obtains the item item in list.
// Returns a pointer to the pointer containing the item item if it is in the list.
// Otherwise returns a NULL pointer.
void** DynamicList_GetItem(DynamicList* list, void* item)
{
	assert(list != NULL);

	for (uint32_t itemId = 0; itemId < list->count; itemId++)
	{
		// we found the item
		if (DynamicList_GetItemIndex(list, itemId) == item) return item;
	}

	if (gLogger != NULL) Logging_LogChannel(u8"Called DynamicList_GetItem with item pointer that is not in the DynamicList", LogChannel_Error);
	// no item
	return NULL;
}

// Removes the item item from the list list if it exists.
// Returns TRUE if it was successfully removed.
// Returns FALSE if it was not.
bool DynamicList_RemoveItem(DynamicList* list, void** item)
{
	assert(list != NULL);
	assert(item != NULL);
	// TODO: find first free item

	// transparent resize
	// don't duplicate if we are above some arbitrary number for memory concerns

	// get ram position of item to be removed
	void** finalPosition = DynamicList_GetItem(list, item);

	if (finalPosition == NULL
		|| finalPosition == EUPHORIA_DYNAMIC_LIST_DELETE_MARKER)
	{
		errno = EINVAL;
		if (gLogger != NULL) Logging_LogChannel(u8"Called DynamicList_RemoveItem with item not in DynamicList!", LogChannel_Error);
		return false;
	}

	// special anti-item operation
	memset(finalPosition, EUPHORIA_DYNAMIC_LIST_DELETE_MARKER, sizeof(uintptr_t));

	return true;
}

// Removes the item at index index from the list list.
bool DynamicList_RemoveItemIndex(DynamicList* list, uint32_t index)
{
	assert(list != NULL);

	void** item = DynamicList_GetItemIndex(list, index);

	if (item == NULL)
	{
		errno = EINVAL;
		if (gLogger != NULL) Logging_LogChannel(u8"Called DynamicList_RemoveItemIndex with invalid index!", LogChannel_Error);
		return false;
	}

	if (!DynamicList_RemoveItem(list, item))
	{
		errno = EINVAL;
		return false;
	}

	return true;
}

// Removes items in list list 
bool DynamicList_RemoveItemSet(DynamicList* list, uint32_t indexStart, uint32_t indexEnd)
{
	assert(list != NULL);
	assert(indexEnd > indexStart);
	assert(indexStart >= 0);
	assert(indexEnd <= list->capacity);

	for (int curItem = indexStart; curItem <= indexEnd; curItem++)
	{
		if (!DynamicList_RemoveItemIndex(list, curItem)) return false;
	}

	DynamicList_compact(list);

	return true;
}

// Resizes the list list to capacity. Capacity must be larger than the current number of items in the list.
bool DynamicList_Resize(DynamicList* list, uint32_t capacity)
{
	assert(list != NULL);

	if (capacity < list->count)
	{
		if (gLogger != NULL) Logging_LogChannel(u8"Tried to resize a DynamicList below its capacity.", LogChannel_Error);

		errno = EINVAL;
		return false;
	}
	assert(capacity > list->count);

	// allocate a newer size. realloc() automatically copies
	uintptr_t newPtr = (uintptr_t)realloc(list->items, sizeof(uintptr_t) * capacity);

	assert(newPtr != NULL);

	list->items = newPtr;

	uintptr_t clearStart = newPtr + sizeof(uintptr_t) * list->capacity; // old capacity
	uintptr_t clearEnd = newPtr + sizeof(uintptr_t) * capacity; // new capacity

	// clear remaining memory 
	memset((void*)clearStart, 0x00, clearEnd - clearStart);

	// set new capacity
	list->capacity = capacity;

	return true;
}

// Internal function: Compact a dynamic list.
void DynamicList_compact(DynamicList* list)
{
	assert(list != NULL);

	int moveAmount = 0;

	void** item;

	for (int curItem = 0; curItem < list->count; curItem++)
	{
		item = DynamicList_GetItemIndex(list, curItem);

		// item doesn't exist.
		if (item == NULL)
		{
			moveAmount++;
		}
		else
		{
			if (item != NULL
				&& curItem >= moveAmount
				&& moveAmount > 0) // check an item exists AND needs to be moved back
			{
				uintptr_t initialLocation = ((uintptr_t)list->items) + curItem * sizeof(uintptr_t);
				uintptr_t finalLocation = ((uintptr_t)list->items) + (curItem - moveAmount) * sizeof(uintptr_t);

				// assert if out of bounds
				assert(finalLocation >= (uintptr_t)list->items);

				// move it!
				memmove((void*)finalLocation, (void*)initialLocation, sizeof(uintptr_t));

				// remove original item
				memset((void*)initialLocation, EUPHORIA_DYNAMIC_LIST_DELETE_MARKER, sizeof(uintptr_t));
			}
		}
	}

	// move list->count by final move amount
	list->count -= moveAmount;
}

// Destroys all items of a dynamic list and then destroys the list.
void DynamicList_destroy(DynamicList* list)
{
	for (uint32_t item = 0; item < list->count; item++)
	{
		DynamicList_RemoveItemIndex(list, item);
	}

	free(list->items);
	free(list);
}