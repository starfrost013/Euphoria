#pragma once
#include "../Euphoria.h"
#include "logging/Logging.h"
#include "console/GVar.h"
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
	Logging_LogAll(u8"Initalising GVars");
	GVar_Init();

	GVar_AddInt("Name", 219132);
	GVar_AddFloat("Name2", 333333.1238);
	GVar_AddString("Name3", "TEST!");

	printf("%d\n", GVar_GetInt("Name"));
	printf("%f\n", GVar_GetFloat("Name2"));

	char* hahahaha = GVar_GetString("Name3");

	printf("%s", hahahaha);


	return true;
}

void Tier0_Shutdown()
{
	Logging_Shutdown();
	NetBase_Shutdown();
}