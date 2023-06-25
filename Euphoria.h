// Euphoria.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// Includes
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <uchar.h>

// TODO: Reference additional headers your program requires here.

#define EUPHORIA_VERSION "0.0.0"
#define EUPHORIA_VERSION_FULL "Euphoria version " EUPHORIA_VERSION " built: "  __DATE__ " " __TIME__

// Defines
// MSVC typedefs
#if _MSC_VER
typedef signed __int8 eu_int8;
typedef unsigned __int8 eu_uint8;
typedef signed __int16 eu_int16;
typedef unsigned __int16 eu_uint16;
typedef signed __int32 eu_int32;
typedef unsigned __int32 eu_uint32;
typedef signed __int64 eu_int64;
typedef unsigned __int64 eu_uint64;

#define EUPHORIA_API __declspec(dllexport)

// GCC typedefs
#elif __GNUC__
typedef __INT8_TYPE__ eu_int8;
typedef __UINT8_TYPE__ eu_uint8;
typedef __INT16_TYPE__ eu_int16;
typedef __UINT16_TYPE__ eu_uint16;
typedef __INT32_TYPE__ eu_int32;
typedef __UINT32_TYPE__ eu_uint32;
typedef __INT64_TYPE__ eu_int64;
typedef __UINT64_TYPE__ eu_uint64;

// we don't use GCC for windows so just define linux here

#define EUPHORIA_API __attribute__((visibility("default")))
#endif

#if _WIN32
// OS configuration
#define EUPHORIA_BUILD_WINDOWS

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
#define EUPHORIA_BUILD_LINUX
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