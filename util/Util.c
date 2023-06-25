#pragma once
#include "Util.h"

void Util_GetCurrentDateString(char **finalArray)
{
	time_t currentTime;
	const struct tm currentTimeInfoPtr;

	assert(finalArray != NULL);

	memset(&currentTimeInfoPtr, 0x00, sizeof(currentTimeInfoPtr));
	memset(&currentTime, 0x00, sizeof(currentTime));

	time(&currentTime);

	localtime_s(&currentTimeInfoPtr, &currentTime);

	*finalArray = asctime(&currentTimeInfoPtr);
}

bool Util_EnumHasFlag(eu_int32 enumValue, eu_int32 flag)
{
	return ((enumValue & flag) == flag);
}