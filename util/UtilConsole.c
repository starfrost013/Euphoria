#pragma once
#include "UtilConsole.h"

void Util_ConsoleSetForegroundColor(ConsoleColor color)
{
	int32_t finalColor = 0;

	finalColor = 30 + color;
	if (color >= CONSOLECOLOR_FIRST_BRIGHT) finalColor = 90 + color;

	char* string = Util_StringFromInt(finalColor);

	char* finalString = strcat("%m", )
}

void Util_ConsoleSetBackgroundColor(ConsoleColor color)
{
	int32_t finalColor = 0;

	finalColor = 40 + color;
	if (color >= CONSOLECOLOR_FIRST_BRIGHT) finalColor = 100 + color;

	char* string = Util_StringFromInt(finalColor);
}

void Util_ConsoleResetForegroundColor(ConsoleColor color)
{
	
}

void Util_ConsoleResetBackgroundColor(ConsoleColor color)
{

}

void Util_ConsoleClearScreen(ConsoleColor color)
{

}