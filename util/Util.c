#pragma once
#include "../Euphoria.h"
#include "Util.h"

void Util_DateGetCurrentString(char **finalArray)
{
	time_t currentTime;
	struct tm currentTimeInfoPtr;

	assert(finalArray != NULL);

	memset(&currentTimeInfoPtr, 0x00, sizeof(currentTimeInfoPtr));
	memset(&currentTime, 0x00, sizeof(currentTime));

	time(&currentTime);

	localtime_s(&currentTimeInfoPtr, &currentTime);

	*finalArray = asctime(&currentTimeInfoPtr);
}

bool Util_EnumHasFlag(int32_t enumValue, int32_t flag)
{
	return ((enumValue & flag) == flag);
}

bool Util_StringBooleanTest(char* string)
{
	assert(string != NULL);

	if (strcmpi(string, "true"))
	{
		return true;
	}
	else if (strcmpi(string, "false"))
	{
		return false;
	}
}

char* Util_StringFromInt(int32_t num)
{
	// 10 digit number as uint32_t max is 2147483647
	char stringPtr[10];
	memset(&stringPtr, 0x00, sizeof(uint32_t) * 8 + 1);
	sprintf_s(&stringPtr, sizeof(char) * 10, "%d", num);
	
	return stringPtr;
}
