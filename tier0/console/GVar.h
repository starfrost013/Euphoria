#pragma once
#include "../../Euphoria.h"
#include "../../util/UtilDynamicList.h"

// GVar
//
// Implements a key-value pair array of engine global variables.

typedef enum GVarType_s
{
	GVarType_Int = 0,
	GVarType_String = 1,
	GVarType_Float = 2,
} GVarType;

typedef struct GVar_s
{
	char* name[16];
	char* value[16];
	GVarType type;
} GVar;

typedef struct GVarList_s
{
	DynamicList* list;
} GVarList;
