# CMakeList.txt : CMake project for Euphoria, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Euphoria")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Euphoria.c" "Euphoria.h" "tier0/net/client/NetClient.c" "tier0/net/server/NetServer.c" "tier0/platform/win32/WinSock.c" "tier0/net/client/NetClient.h" "tier0/platform/win32/WinSock.h"  "tier0/logging/Logging.h" "tier0/net/server/NetServer.h" "util/Util.h" "tier0/tier0.c" "tier0/tier0.h" "util/Util.c" "tier0/logging/Logging.c" "tier0/console/GVar.c" "tier0/console/GVar.h")

# Link API ibraries
if (WIN32)
	if (!MSVC)
		message(FATAL_ERROR "Only MSVC is supported on win32")
	else()
		find_library(LIBRARY_WIN32_WSOCK32 wsock32.lib)
		find_library(LIBRARY_WIN32_WS232 ws2_32.lib)

		target_link_libraries(${PROJECT_NAME} ws2_32)
		target_link_libraries(${PROJECT_NAME} wsock32)
	endif()
else()
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Euphoria PROPERTY C_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
