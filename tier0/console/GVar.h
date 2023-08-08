#pragma once
#include "../../Euphoria.h"
#include "../../util/UtilDynamicList.h"

// 
// GVar.h: Defines a key-value pair array of engine global variables.
// 

// Define maximum size of gvar name.
#define EUPHORIA_GVAR_MAX_SIZE 32

// Nonsense value that will never be reached
#define EUPHORIA_GVAR_NO_FLOAT 9.90000026e+09f

typedef enum GVarType_s
{
	GVarType_Int = 0,
	GVarType_String = 1,
	GVarType_Float = 2,
} GVarType;

typedef struct GVar_s
{
	char name[EUPHORIA_GVAR_MAX_SIZE];
	char value[EUPHORIA_GVAR_MAX_SIZE];
	GVarType type;
} GVar;

DynamicList* gGvarList;

void GVar_Init();

GVar* GVar_new();

bool GVar_AddInt(char* name, int32_t value);
bool GVar_AddString(char* name, char* value);
bool GVar_AddFloat(char* name, float value);

GVar* GVar_GetGVar(char* name);

uint32_t GVar_GetInt(char* name);
char* GVar_GetString(char* name);
float GVar_GetFloat(char* name);

bool GVar_SetInt(char* name, int32_t value);
bool GVar_SetString(char* name, char* value);
bool GVar_SetFloat(char* name, float value);

bool GVar_Delete(char* name);

void GVar_destroy(GVar* gVar);

void GVar_Shutdown();