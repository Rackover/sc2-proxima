// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma once

#pragma warning(disable: 4100)

#define __STDC_LIB_EXT1__ 1
#define __STDC_WANT_LIB_EXT1__ 1

// add headers that you want to pre-compile here
#include <cstdint>
#include <map>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <functional>
#include <optional>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <filesystem>
#include <string>

#include "Winsock2.h"
#include "Ws2tcpip.h"
#include <WinDNS.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <assert.h>
#include <Lmcons.h>
#include "iphlpapi.h"

#include <shellapi.h>

// Useful tools from the IW4x Project
#include "Memory.hpp"
#include "Hooking.hpp"
#include "Logger.hpp"

#define SUPCOM2_APPID 40100

namespace Proxima
{
	class Client;
	class Server;
}

using namespace std::literals::string_literals;

#include "net.proto.h"

#include "steam_api/Steam.hpp"
#include "Callbacks.hpp"

#include "Profile.hpp"

#include "Auth.hpp"
#include "FileSystem.hpp"
#include "Stats.hpp"
#include "Leaderboards.hpp"
#include "Networking.hpp"

#include "Client.hpp"
#include "Server.hpp"
#include "ServerList.hpp"

#pragma comment(lib, "Ws2_32.lib")

#endif //PCH_H
