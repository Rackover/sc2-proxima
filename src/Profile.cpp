#include "pch.h"

namespace Proxima
{
	Profile Profile::MakeDefaultProfile()
	{
		auto profile = Profile();

		profile.steamID = GenerateSteamIDFromMacAddress();
		profile.name = GetDefaultUsername();
		profile.hostPort = Networking::DEFAULT_PORT;

		return profile;
	}

	CSteamID Profile::GenerateSteamIDFromMacAddress()
	{
		uint32 id = 0;

		IP_ADAPTER_INFO* AdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(sizeof(IP_ADAPTER_INFO) * 32));
		DWORD dwBufLen = sizeof(IP_ADAPTER_INFO) * 32;

		DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
		if (dwStatus != ERROR_SUCCESS)
		{
			id = 0xDEADBEEF; // no adapters.      
		}
		else if (AdapterInfo)
		{
			for (size_t i = 0; i < AdapterInfo->AddressLength; i++)
			{
				id += static_cast<uint32>(AdapterInfo->Address[i]) << i;
			}
		}

		CSteamID steamID;

		steamID.m_comp.m_EAccountType = EAccountType::k_EAccountTypeIndividual;
		steamID.m_comp.m_EUniverse = EUniverse::k_EUniversePublic;
		steamID.m_comp.m_unAccountInstance = 1;
		steamID.m_comp.m_unAccountID = id;

		free(AdapterInfo);

		return steamID;
	}

	std::string Profile::GetDefaultUsername()
	{
		char username[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserNameA(username, &username_len);

		return username;
	}
}