#pragma once
#include "../Euphoria.h"

// Date utilities
void Util_DateGetCurrentString(char **finalArray);

// Enum utilities
bool Util_EnumHasFlag(eu_int32 enumValue, eu_int32 flag);

// String utilities
bool Util_StringBooleanTest(char* string);