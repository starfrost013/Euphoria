#pragma once
#include "../Euphoria.h"

//
//	Util.h: Implements "general" util functions.
//

// Date utilities
void Util_DateGetCurrentString(char **finalArray);

// Enum utilities
bool Util_EnumHasFlag(int32_t enumValue, int32_t flag);

// String utilities
char* Util_StringFromInt(int32_t num);
bool Util_StringBooleanTest(char* string);