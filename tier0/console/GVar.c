#pragma once
#include "GVar.h"
#include "../logging/Logging.h"

// Internal functions
GVar** GVar_GetGVarPtr(char* name);

void GVar_Init()
{
	gGvarList = DynamicList_new(50);
}

GVar* GVar_new()
{
	GVar* gVar = (GVar*)malloc(sizeof(GVar));

	assert(gVar != NULL);

	memset(gVar->name, 0x00, sizeof(char) * EUPHORIA_GVAR_MAX_SIZE);
	memset(gVar->value, 0x00, sizeof(char) * EUPHORIA_GVAR_MAX_SIZE);

	return gVar;
}

bool GVar_AddInt(char* name, int32_t value)
{
	GVar* gVar = GVar_new();
	
	if (strlen(name) > EUPHORIA_GVAR_MAX_SIZE)
	{
		Logging_LogChannel("GVar_AddInt: name too long!", LogChannel_Error);
		return false;
	}

	gVar->type = GVarType_Int;

	strcpy_s(gVar->name, 32, name);


	snprintf(gVar->value, 32, "%d", value);

	DynamicList_AddItem(gGvarList, gVar);

	return true;
}

bool GVar_AddString(char* name, char* value)
{
	GVar* gVar = GVar_new();

	if (strlen(name) > EUPHORIA_GVAR_MAX_SIZE)
	{
		Logging_LogChannel("GVar_AddString: name too long!", LogChannel_Error);
		return false;
	}

	strcpy_s(gVar->name, 32, name);

	gVar->type = GVarType_String;

	strcpy_s(gVar->value, 32, value);

	DynamicList_AddItem(gGvarList, gVar);

	return true;
}

bool GVar_AddFloat(char* name, float value)
{
	GVar* gVar = GVar_new();

	if (strlen(name) > EUPHORIA_GVAR_MAX_SIZE)
	{
		Logging_LogChannel("GVar_AddInt: name too long!", LogChannel_Error);
		return false;
	}

	strcpy_s(gVar->name, 32, name);

	gVar->type = GVarType_Float;

	snprintf(gVar->value, 32, "%f", value);

	DynamicList_AddItem(gGvarList, gVar);

	return true;
}

uint32_t GVar_GetInt(char* name)
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		GVar** gVarPtr = (GVar**)DynamicList_GetItemIndex(gGvarList, itemId);

		if (gVarPtr != NULL)
		{
			GVar* gVar = *gVarPtr;

			if (strcmp(gVar->name, name) == 0
				&& gVar->type == GVarType_Int)
			{
				int32_t value = atoi(gVar->value);
				return value;
			}
		}
	}

	return NULL;
}

char* GVar_GetString(char* name)
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		GVar** gVarPtr = (GVar**)DynamicList_GetItemIndex(gGvarList, itemId);

		if (gVarPtr != NULL)
		{
			GVar* gVar = *gVarPtr;

			if (strcmp(gVar->name, name) == 0
				&& gVar->type == GVarType_String) return gVar->value;
		}
	}

	return NULL;
}

float GVar_GetFloat(char* name)
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		GVar** gVarPtr = (GVar**)DynamicList_GetItemIndex(gGvarList, itemId);

		if (gVarPtr != NULL)
		{
			GVar* gVar = *gVarPtr;

			if (strcmp(gVar->name, name) == 0
				&& gVar->type == GVarType_Float)
			{
				float value = atof(gVar->value);
				return value;
			}
		}

	}

	return EUPHORIA_GVAR_NO_FLOAT;
}

GVar* GVar_GetGVar(char* name)
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		GVar** gVarPtr = (GVar**)DynamicList_GetItemIndex(gGvarList, itemId);

		if (gVarPtr != NULL)
		{
			GVar* gVar = *gVarPtr;

			if (strcmp(gVar->name, name) == 0) return gVar;
		}
	}

	return NULL;
}

GVar** GVar_GetGVarPtr(char* name)
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		GVar** gVarPtr = (GVar**)DynamicList_GetItemIndex(gGvarList, itemId);
		GVar* gVar = *gVarPtr;

		if (strcmp(gVar->name, name) == 0) return gVarPtr;
	}

	return NULL;
}

bool GVar_SetInt(char* name, int32_t value)
{
	GVar* gVar = GVar_GetGVar(name);

	if (gVar == NULL)
	{
		Logging_LogChannel("GVar_SetInt: name not in GVar List!", LogChannel_Error);
		return false;
	}

	snprintf(gVar->value, 32, "%d", value);
	return true;
}

bool GVar_SetString(char* name, char* value)
{
	GVar* gVar = GVar_GetGVar(name);

	if (gVar == NULL)
	{
		Logging_LogChannel("GVar_SetInt: name not in GVar List!", LogChannel_Error);
		return false;
	}

	strcpy(gVar->value, value);

	return true;
}

bool GVar_SetFloat(char* name, float value)
{
	GVar* gVar = GVar_GetGVar(name);

	if (gVar == NULL)
	{
		Logging_LogChannel("GVar_SetInt: name not in GVar List!", LogChannel_Error);
		return false;
	}

	snprintf(gVar->value, 32, "%f", value);
	return true;
}

bool GVar_Delete(char* name)
{
	GVar** gVarPtr = GVar_GetGVarPtr(name);

	if (gVarPtr == NULL)
	{
		return false;
	}
	else
	{
		GVar* gVar = *gVarPtr;
		DynamicList_RemoveItem(gGvarList, gVarPtr);

		GVar_destroy(gVar);
		DynamicList_compact(gGvarList);
		return true;
	}
}

void GVar_destroy(GVar* gVar)
{
	free((void*)gVar);
}

void GVar_Shutdown()
{
	for (int itemId = 0; itemId < gGvarList->count; itemId++)
	{
		// get gvar (dynamic list is list of pointers)
		GVar* gVar = (GVar*)*DynamicList_GetItemIndex(gGvarList, itemId);
		
		// Remove the item!
		GVar_destroy(gVar);
	}

	DynamicList_destroy(gGvarList);
}