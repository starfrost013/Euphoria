#pragma once
#include "Util.h"
#include "../Euphoria.h"
/*
	This is a dynamic list class that takes arbitrary pointers as items and asserts if anything is wrong.
	You have to cast the type you're adding to uintptr_t* in order to use this.
	I recommend having every item you add to one of these be the same.
*/

typedef struct
{
	eu_uint32 capacity;
	eu_uint32 count;
	void* items;

} DynamicList;

DynamicList* DynamicList_new(eu_uint32 capacity);

// convert item to void* 
bool DynamicList_AddItem(DynamicList* list, void* item);

void* DynamicList_GetItem(DynamicList* list, void* item);

void* DynamicList_GetItemIndex(DynamicList* list, eu_uint32 index);

bool DynamicList_RemoveItem(DynamicList* list, void* item);

bool DynamicList_RemoveItemIndex(DynamicList* list, eu_uint32 index);

bool DynamicList_Resize(DynamicList* list, eu_uint32 capacity);

void DynamicList_destroy(DynamicList* list);