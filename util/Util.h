#pragma once
#include "../Euphoria.h"

// Date utilities
void Util_DateGetCurrentString(char **finalArray);

// Enum utilities
bool Util_EnumHasFlag(int32_t enumValue, int32_t flag);

// String utilities
bool Util_StringBooleanTest(char* string);