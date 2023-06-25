#pragma once
#include "../Euphoria.h"
#include "logging/Logging.h"
#ifdef EUPHORIA_BUILD_WINDOWS
#include "platform/win32/WinSock.h"
#endif

// Tier 0:
// Logging, GVar/netprop, network, etc

bool Tier0_Init()
{
	Logging_Init();
	Logging_LogAll("Initialise NetBase");
	NetBase_Init();
	return true;
}

void Tier0_Shutdown()
{
	Logging_Shutdown();
	NetBase_Shutdown();
}