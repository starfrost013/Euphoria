#pragma once
#include "../Euphoria.h"
#include "logging/Logging.h"
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
	return true;
}

void Tier0_Shutdown()
{
	Logging_Shutdown();
	NetBase_Shutdown();
}