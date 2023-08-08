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
	printf("%s\n", GVar_GetString("Name3"));

	GVar_SetInt("Name", 234813213);
	GVar_SetFloat("Name2", 44444.4444);
	GVar_SetString("Name3", "TEST! (CHANGED)")
		;
	printf("%d\n", GVar_GetInt("Name"));
	printf("%f\n", GVar_GetFloat("Name2"));
	printf("%s\n", GVar_GetString("Name3"));

	GVar_Delete("Name2");

	GVar* gVar = GVar_GetGVar("Name3");
	
	float hello = GVar_GetFloat("Name2");

	assert(hello == EUPHORIA_GVAR_NO_FLOAT);

	return true;
}

void Tier0_Shutdown()
{
	GVar_Shutdown();
	Logging_Shutdown();
	NetBase_Shutdown();
}