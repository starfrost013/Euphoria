#pragma once
#include "../tier0/logging/Logging.h"
#include "Util.h"
#include "UtilDynamicList.h"

#define EUPHORIA_DYNAMIC_LIST_REALLOC_MAX_MULTIPLY 50000


DynamicList* DynamicList_new(eu_uint32 capacity)
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

	newList->items = malloc(sizeof(void*) * capacity);

	return newList;
}

bool DynamicList_AddItem(DynamicList* list, void* item)
{
	assert(list != NULL);
	assert(item != NULL);
	// TODO: find first free item

	// transparent resize
	// don't duplicate if we are above some arbitrary number for memory concerns

	list->count++;

	if (list->count > list->capacity)
	{
		eu_uint32 newCapacity = list->capacity * 2;

		if (list->capacity > EUPHORIA_DYNAMIC_LIST_REALLOC_MAX_MULTIPLY) newCapacity = list->capacity * 1.1;

		DynamicList_Resize(list, newCapacity);
	}

	// get ram position of final item
	uintptr_t finalPosition = ((uintptr_t)list->items) + (sizeof(uintptr_t) * list->count);

	memcpy(finalPosition, &item, sizeof(uintptr_t));

	return true;
}

void* DynamicList_GetItemIndex(DynamicList* list, eu_uint32 index)
{
	assert(list != NULL);
	assert(index < list->count);

	return ((uintptr_t)list->items + (sizeof(uintptr_t) * index));
}

void* DynamicList_GetItem(DynamicList* list, void* item)
{
	assert(list != NULL);

	for (eu_uint32 itemId = 0; itemId < list->count; itemId++)
	{
		// we found the item
		if (((uintptr_t)list->items) + (sizeof(uintptr_t) * itemId) == item) return item;
	}

	if (gLogger != NULL) Logging_LogChannel("Called DynamicList_GetItem with item pointer that is not in the DynamicList", LogChannel_Error);
	// no item
	return NULL;
}

bool DynamicList_RemoveItem(DynamicList* list, void* item)
{
	assert(list != NULL);
	assert(item != NULL);
	// TODO: find first free item

	// transparent resize
	// don't duplicate if we are above some arbitrary number for memory concerns

	list->count--;

	if (list->count > list->capacity)
	{
		eu_uint32 newCapacity = list->capacity * 2;

		if (list->capacity > EUPHORIA_DYNAMIC_LIST_REALLOC_MAX_MULTIPLY) newCapacity = list->capacity * 1.1;

		DynamicList_Resize(list, newCapacity);
	}

	// get ram position of item to be removed
	uintptr_t finalPosition = (uintptr_t)DynamicList_GetItem(list, item);

	if (finalPosition == NULL)
	{
		errno = EINVAL;
		if (gLogger != NULL) Logging_LogChannel("Called DynamicList_RemoveItem with item not in .", LogChannel_Error);
		return false;
	}

	// destroy the item
	free(&item);

	// special anti-item operation
	memset(finalPosition, 0x00, sizeof(uintptr_t));

	return true;
}

bool DynamicList_RemoveItemIndex(DynamicList* list, eu_uint32 index)
{
	assert(list != NULL);

	void* item = DynamicList_GetItemIndex(list, index);

	if (item == NULL)
	{
		errno = EINVAL;
		if (gLogger != NULL) Logging_LogChannel("Called DynamicList_RemoveItemIndex with invalid index!", LogChannel_Error);
		return false;
	}

	if (!DynamicList_RemoveItem(list, item))
	{
		errno = EINVAL;
		return false;
	}

	return true;
}

bool DynamicList_Resize(DynamicList* list, eu_uint32 capacity)
{
	assert(list != NULL);

	if (capacity < list->count)
	{
		if (gLogger != NULL) Logging_LogChannel("Tried to resize a DynamicList below its capacity.", LogChannel_Error);

		errno = EINVAL;
		return false;
	}
	assert(capacity > list->count);

	// allocate a newer size
	void* newPtr = realloc(list->items, sizeof(void*) * capacity);

	// copy items
	for (eu_uint32 item = 0; item < list->count; item++)
	{
		uintptr_t newLocation = (uintptr_t)newPtr + (sizeof(uintptr_t) * item);
		memmove(newLocation, (uintptr_t)list->items + (sizeof(void*) * item), sizeof(uintptr_t));
	}

	// free original list
	free(list->items);

	// set new items
	list->items = newPtr;

	// set new capacity
	list->capacity = capacity;

	return true;
}

// Destroys all items of a dynamic list and then destroys the list.
void DynamicList_destroy(DynamicList* list)
{
	for (eu_uint32 item = 0; item < list->count; item++)
	{
		DynamicList_RemoveItemIndex(list, item);
	}

	free(list->items);
	free(list);
}