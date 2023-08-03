#pragma once
#include "../Euphoria.h"
#include "Util.h"

char gStringFromIntPtr[10];

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

bool Util_StringFromBoolean(char* string)
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
	memset(&gStringFromIntPtr, 0x00, sizeof(char) * 10);
	sprintf_s(&gStringFromIntPtr, sizeof(char) * 10, "%d", num);
	
	return &gStringFromIntPtr;
}
