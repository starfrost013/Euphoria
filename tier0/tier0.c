#pragma once
#include "../Euphoria.h"
#include "logging/Logging.h"
#include "../util/UtilConsole.h"
#include "../util/UtilDynamicList.h"
#ifdef EUPHORIA_BUILD_WINDOWS
#include "platform/windows/WinSock.h"
#endif

// Tier 0:
// Logging, GVar/netprop, network, etc

bool Tier0_Init()
{
	printf(u8"Initialising Tier 0\n");
	Logging_Init();
	Logging_LogAll(EUPHORIA_VERSION_FULL);
	Logging_LogAll(u8"Initialise NetBase");
	NetBase_Init();

	// Temporary stresstest

	Logging_LogAll(u8"Dynamic List stress for Tier 0");
	DynamicList* list = DynamicList_new(50);

	char characterPtr[100];
	memset(&characterPtr, 0x00, sizeof(char) * 100);

	// Generate 50 random characters
	time_t currentTime;

	srand((unsigned)time(&currentTime)); // seed rand current second

	Logging_LogAll(u8"random chars (50, 100) - add, resize");

	// generate and add to list
	for (int charNum = 0; charNum < 50; charNum++)
	{
		characterPtr[charNum] = (rand() % 223) + 32; 

		if (!DynamicList_AddItem(list, (void*)&characterPtr[charNum])) Logging_LogAll(u8"Failed to add - this is intentional");
	}

	printf("%s\n", characterPtr);

	for (int charNum = 0; charNum < 50; charNum++)
	{
		// get pointer to the character
		char** item = (char**)DynamicList_GetItemIndex(list, charNum);

		if (item != NULL)
		{
			char realChar = **item; // deref to get actual current char
			putchar(realChar);
		}
	}

	printf("\n");

	// generate and add to list
	for (int charNum = 50; charNum < 100; charNum++)
	{
		characterPtr[charNum] = (rand() % 223) + 32;
		if (charNum == 99) characterPtr[charNum] = '\0';

		if (!DynamicList_AddItem(list, (void*)&characterPtr[charNum])) Logging_LogAll(u8"Failed to add item");
	}

	printf("%s\n", characterPtr);

	for (int charNum = 0; charNum < 100; charNum++)
	{
		// get pointer to the character
		char** item = (char**)DynamicList_GetItemIndex(list, charNum);

		if (item != NULL)
		{
			char realChar = **item; // deref to get actual current char
			putchar(realChar);
		}
	}

	printf("\n");

	Logging_LogAll(u8"100 random chars- remove first half");

	DynamicList_RemoveItemSet(list, 0, 49);

	Logging_LogAll(u8"Remove item 25");

	DynamicList_RemoveItemIndex(list, 25);

	Logging_LogAll(u8"Compact list");

	DynamicList_compact(list);

	for (int charNum = 0; charNum < 100; charNum++)
	{
		// get pointer to the character
		char** item = (char**)DynamicList_GetItemIndex(list, charNum);

		if (item != NULL)
		{
			char realChar = **item; // deref to get actual current char
			putchar(realChar);
		}
	}

	printf("\n");

	DynamicList_destroy(list);

	Util_ConsoleClearScreen();
	Util_ConsoleSetForegroundColor(ConsoleColor_BrightBlue);
	Util_ConsoleSetBackgroundColor(ConsoleColor_BrightWhite);
	Logging_LogAll(u8"hahaha");
	Logging_LogChannel(u8"hahaha", LogChannel_Error);
	Logging_LogChannel(u8"hahaha", LogChannel_Warning);
	Logging_LogChannel(u8"hahaha", LogChannel_Fatal);

	Util_ConsoleResetForegroundColor();
	Util_ConsoleResetBackgroundColor();
	Logging_LogChannel(u8"hahaha", LogChannel_Message);


	return true;
}

void Tier0_Shutdown()
{
	Logging_Shutdown();
	NetBase_Shutdown();
}