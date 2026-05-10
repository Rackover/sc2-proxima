#include "pch.h"


Proxima::Networking::HostedLobby Proxima::Networking::currentLobby{};
bool Proxima::Networking::isFakeJoinLobbyAvailable = false;

void Proxima::Networking::AddFakeJoinOnlyLobby(const std::string& ipAddress)
{
	NET_ADDRESS_INFO addressInfo{};
	USHORT portNumber{};

	wchar_t* destination = new wchar_t[ipAddress.size()+1];
	ZeroMemory(destination, (ipAddress.size() +1) * sizeof(wchar_t)),

	MultiByteToWideChar(CP_ACP, 0, ipAddress.c_str(), ipAddress.size(), destination, ipAddress.size());
	const std::wstring wideIP(destination, ipAddress.size());

	DWORD result = ParseNetworkString(wideIP.c_str(), NET_STRING_IPV4_ADDRESS | NET_STRING_IPV4_SERVICE, &addressInfo, &portNumber, NULL);

	delete[] destination;

	if (result == ERROR_SUCCESS)
	{
		currentLobby.address = static_cast<uint32>(addressInfo.Ipv4Address.sin_addr.S_un.S_addr);
		currentLobby.port = portNumber == 0 ? DEFAULT_PORT : portNumber;
		isFakeJoinLobbyAvailable = true;
	}
	else
	{
		isFakeJoinLobbyAvailable = false;
	}
}

bool Proxima::Networking::GetFakeJoinOnlyLobby(OUT const HostedLobby*& data)
{
	data = &currentLobby;
	return isFakeJoinLobbyAvailable;
}


__declspec(naked) void Proxima::Networking::SetConnectionAdapterTypeForceUDP()
{
	_asm
	{
		// 1 => Seems to be traditional connector, works ? Listens on UDP port 1000
		// 2 and 3 are udp connector
		// 2 hangs when creating lobby, NOT LISTENING
		// 3 can create lobby but seems to be using Steam, NOT LISTENING
		// 4 is Steam connector, default

		// Force adapter type to udp
		mov esi, 1

		// Original code
		push ebp
		mov ebp, esp
		and esp, 0xFFFFFFF8

		// Return
		push 0xAEEB26
		retn
	}
}

void Proxima::Networking::InjectEndpointIntoConnxHook(uint32 connexionInfo)
{
	// We inject the IP:PORT we inputed during the "game search" back into the adapter
	const HostedLobby* lobby;
	if (GetFakeJoinOnlyLobby(lobby))
	{
		uint32* address = reinterpret_cast<uint32*>(connexionInfo + 56);
		uint16* port = reinterpret_cast<uint16*>(connexionInfo + 68);

		uint32 lobbyAddress = ntohl(lobby->address);

		*address = lobbyAddress;
		*port = lobby->port;
	}
}

__declspec(naked) void Proxima::Networking::InjectEndpointIntoConnx()
{
	_asm
	{
		pushad
		push esi
		call InjectEndpointIntoConnxHook
		pop esi
		popad

		// Original code
		sub esp, 0xC
		lea ecx, [esp]

		// Return 
		push 0xAF7936
		retn
	}
}

char __stdcall Proxima::Networking::SetupLanGame_Hook(int a1, int a2, const char* scenarioName, const char* scenarioPath)
{
	// This calls the "setup LAN game" normal function, we act right _after it_
	const auto result = Utils::Hook::Call<char __stdcall(const char*, const char*)>(0xC4B2E0)(scenarioName, scenarioPath);
	
	constexpr uint8_t LOBBY_READY = 3; // 2 is "connection failed", 0 is "ongoing"

	// This is necessary to make the LAN Connection Manager accept incoming connections
	auto connexionManager = Utils::Hook::Get<gpg_ConnectionManager>(0x18F2060);
	*(connexionManager.lobbyStatus) = LOBBY_READY;

	// And this is necessary to send the callback to the main menu UI that "Hosting..." is completed. Otherwise we wait forever
	auto ongoingConnectionStatus = reinterpret_cast<int*>(0x18F609C);
	*ongoingConnectionStatus = LOBBY_READY;

	return result;
}

void InjectPortIntoHost_Hook(const uint32_t localSessionManagerInstance)
{
	// Before hosting, we inject our preferred port into the gameSession which is referenced by the Game Session manager
	if (localSessionManagerInstance > 0)
	{
		auto defaultPort = reinterpret_cast<uint16_t*>(localSessionManagerInstance + 68);
		assert(*defaultPort == 1000);

		*defaultPort = Proxima::Client::GetPreferredHostPort();
	}

}

__declspec(naked) void InjectPortIntoHost_Stub()
{
	_asm
	{
		pushad
		push ecx
		call InjectPortIntoHost_Hook
		pop ecx
		popad

		push 0xFFFFFFFF
		push 0x105F348

		push 0xAEAB37
		retn
	}
}

void Proxima::Networking::Initialize()
{
	// Instead of calling the traditional "Host" multiplayer, we cacll the "Host" LAN Game instead, which is still present in the game
	// It's not very different from hosting the normal multiplayer since we override the adapter type anyway... maybe this is not necessary! But it works well
	Utils::Hook(0xC4C099, SetupLanGame_Hook, HOOK_CALL).install()->quick();

	// Force every adapter type set to 1 (LAN NET)
	// In the game code it is otherwise always forced to 3 (Steamworks P2P connection)
	Utils::Hook(0xAEEB20, SetConnectionAdapterTypeForceUDP, HOOK_JUMP).install()->quick();

	// Whenever we join a game, we inject the IP:Port that was supplied during the "game search"
	Utils::Hook(0xAF7930, InjectEndpointIntoConnx, HOOK_JUMP).install()->quick();

	Utils::Hook(0xAEAB30, InjectPortIntoHost_Stub, HOOK_JUMP).install()->quick();

}
