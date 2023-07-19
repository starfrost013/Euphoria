#pragma once
#include "Util.h"
#include "../Euphoria.h"
/*
	This is a dynamic list class that takes arbitrary pointers as items and asserts if anything is wrong.
	You have to cast the type you're adding to void** in order to use this.
	I recommend having every item you add to one of these be the same.
	The pointer returned is a pointer to the pointer to the item in the item list of the list.
	You have to dereference twice to get the list.
	Free the item after you remove it from the list.

	Todo:
	- Compaction.
*/

typedef struct
{
	uint32_t capacity;
	uint32_t count;
	void* items;

} DynamicList;

DynamicList* DynamicList_new(uint32_t capacity);

// convert item to void* 
bool DynamicList_AddItem(DynamicList* list, void* item);

void** DynamicList_GetItem(DynamicList* list, void* item);

void** DynamicList_GetItemIndex(DynamicList* list, uint32_t index);

bool DynamicList_RemoveItem(DynamicList* list, void** item);

bool DynamicList_RemoveItemIndex(DynamicList* list, uint32_t index);

bool DynamicList_RemoveItemSet(DynamicList* list, uint32_t indexStart, uint32_t indexEnd);

bool DynamicList_Resize(DynamicList* list, uint32_t capacity);

void DynamicList_compact(DynamicList* list);

void DynamicList_destroy(DynamicList* list);