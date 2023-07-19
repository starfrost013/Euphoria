// Euphoria.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// Includes
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <uchar.h>

// TODO: Reference additional headers your program requires here.

#define EUPHORIA_VERSION "0.0.0"
#define EUPHORIA_VERSION_FULL "Euphoria version " EUPHORIA_VERSION " built: "  __DATE__ " " __TIME__

// Defines
// MSVC typedefs
#if _MSC_VER


#define EUPHORIA_API __declspec(dllexport)

// GCC typedefs
#elif __GNUC__
// we don't use GCC for windows so just define linux here

#define EUPHORIA_API __attribute__((visibility("default")))
#endif

#if _WIN32
// OS configuration

// Assume MSVC
#include <io.h>
#include <fcntl.h>

// Win32 specific includes
#include <WinSock2.h>
#include <WS2tcpip.h>

// Win32 macros to bridge the difference between BSD and Winsock sockets
#define SOCKETVALID(s) ((s) != INVALID_SOCKET);
#define SOCKETERROR (WSAGetLastError());
#define SOCKETCLOSE(s) closesocket(s);

#else // assume linux otherwise
// Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  // Needed for getaddrinfo() and freeaddrinfo() 
#include <unistd.h> // Needed for close()

typedef SOCKET int
#define SOCKETVALID(s) ((s) >= 0);
#define SOCKETERROR() (errno)
#define SOCKETCLOSE() close(s)
#endif