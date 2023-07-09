#pragma once

#include "../../../Euphoria.h"
#ifdef EUPHORIA_BUILD_WINDOWS

#include "WinSock.h"

bool NetBase_Init()
{
	WSADATA wsaData;
	memset(&wsaData, 0x00, sizeof wsaData);

	int wsaInitResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	return (wsaInitResult == 0);
}

void NetBase_Shutdown()
{
	WSACleanup();
}
#endif