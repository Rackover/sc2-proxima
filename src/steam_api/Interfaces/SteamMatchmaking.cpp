#include "pch.h"
#include "SteamMatchmaking.hpp"

STEAM_IGNORE_WARNINGS_START

namespace Steam
{
	int Matchmaking::GetFavoriteGameCount()
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Matchmaking::GetFavoriteGame(int iGame, AppId_t* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, uint32* pRTime32LastPlayedOnServer)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	int Matchmaking::AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Matchmaking::RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	SteamAPICall_t Matchmaking::RequestLobbyList()
	{
		DUMP_FUNC_NAME();

		LobbyMatchList_t data{};

		const Proxima::Networking::HostedLobby* lobby;
		if (Proxima::Networking::GetFakeJoinOnlyLobby(OUT lobby))
		{
			data.m_nLobbiesMatching = 1;
		}

		return Steam::callbacks->GetResultsClient()->AddCallResult(data.k_iCallback, &data, sizeof(data));;
	}

	void Matchmaking::AddRequestLobbyListStringFilter(const char* pchKeyToMatch, const char* pchValueToMatch, ELobbyComparison eComparisonType)
	{
	}

	void Matchmaking::AddRequestLobbyListNumericalFilter(const char* pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
	{
	}

	void Matchmaking::AddRequestLobbyListNearValueFilter(const char* pchKeyToMatch, int nValueToBeCloseTo)
	{
		// Supreme commander 2 uses this for the search field
		// we can use it to create a fake "lobby" to join
		if (pchKeyToMatch)
		{
			std::string req = pchKeyToMatch;
			if (req.starts_with("tag_"))
			{
				req = req.substr(4);

				Proxima::Networking::AddFakeJoinOnlyLobby(req);
			}
		}

	}

	void Matchmaking::AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
	{
		DUMP_FUNC_NAME();
	}

	void Matchmaking::AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter)
	{
		DUMP_FUNC_NAME();
	}

	void Matchmaking::AddRequestLobbyListResultCountFilter(int cMaxResults)
	{
		DUMP_FUNC_NAME();
	}

	CSteamID Matchmaking::GetLobbyByIndex(int iLobby)
	{
		DUMP_FUNC_NAME();
		CSteamID id = Proxima::Client::GetSteamID();
		id.m_comp.m_EAccountType = 8;

		return id;
	}

	SteamAPICall_t Matchmaking::CreateLobby(ELobbyType eLobbyType, int cMaxMembers)
	{
		DUMP_FUNC_NAME();
		//uint64_t result = Callbacks::RegisterCall();
		//LobbyCreated* retvals = ::Utils::Memory::Allocate<LobbyCreated>();
		//CSteamID id{};

		//id.m_comp.m_unAccountID = 1337132;
		//id.m_comp.m_EUniverse = 1;
		//id.m_comp.m_EAccountType = 8;
		//id.m_comp.m_unAccountInstance = 0x40000;

		//retvals->m_eResult = 1;
		//retvals->m_ulSteamIDLobby = id;

		//Callbacks::ReturnCall(retvals, sizeof(LobbyCreated), LobbyCreated::CallbackID, result);*/

		//Matchmaking::JoinLobby(id);

		LobbyCreated_t data{};

		data.m_eResult = EResult::k_EResultOK;

		CSteamID id = Proxima::Client::GetSteamID();
		id.m_comp.m_EAccountType = 8;

		data.m_ulSteamIDLobby = id.m_unAll64Bits;

		return Steam::callbacks->GetResultsClient()->AddCallResult(data.k_iCallback, &data, sizeof(data));
	}

	SteamAPICall_t Matchmaking::JoinLobby(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		//uint64_t result = Callbacks::RegisterCall();
		//LobbyEnter* retvals = ::Utils::Memory::Allocate<LobbyEnter>();
		//retvals->m_bLocked = false;
		//retvals->m_EChatRoomEnterResponse = 1;
		//retvals->m_rgfChatPermissions = 0xFFFFFFFF;
		//retvals->m_ulSteamIDLobby = steamIDLobby;

		//Callbacks::ReturnCall(retvals, sizeof(LobbyEnter), LobbyEnter::CallbackID, result);

		return 0;
	}

	void Matchmaking::LeaveLobby(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		//Components::Party::RemoveLobby(steamIDLobby);
	}

	bool Matchmaking::InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
	{
		DUMP_FUNC_NAME();
		return true;
	}

	int Matchmaking::GetNumLobbyMembers(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		return 1;
	}

	CSteamID Matchmaking::GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
	{
		DUMP_FUNC_NAME();
		return SteamUser()->GetSteamID();
	}

	const char* Matchmaking::GetLobbyData(CSteamID steamIDLobby, const char* pchKey)
	{
		DUMP_FUNC_NAME();

		const Proxima::Networking::HostedLobby* lobby;
		if (Proxima::Networking::GetFakeJoinOnlyLobby(OUT lobby))
		{
			// Supcom2 is not very safe with lobby info - if any member is missing, it will crash!
			static std::unordered_map<std::string, std::string> fakeLobbyInfos = { 
				{"LobbyReady","1"},
				{"Ranked", "1"},
				{"OwnerId", "1"},
				{"ScenarioName", "sc2_mp_205"},
				{"ScenarioFilePath", "/maps/sc2_mp_205/sc2_mp_205_scenario.lua"},
				{"VictoryCondition", "demoralization"},
				{"CheatsEnabled", "1"},
				{"FogOfWar", "1"},
				{"PreBuiltUnits", "1"},
				{"NoRushOption", "1"},
				{"AllowObservers", "1"},
				{"MaxSlots", "2"},
				{"SlotsInUse", "1"},
				{"Timeouts", "1"},
				{"Unitcap", "1"},
				{"HasPassword", "0"},
				{"PrivateGame", "0"},
				{"DLC1Enabled", "1"},
				{"Password", ""},
				{"GSMLobbyType", ""},
				{"MinRanking", ""},
				{"MaxRanking", ""},
				{"AverageRanking", ""},
			};

			if (pchKey == "name"s)
			{
				return lobby->name.c_str();
			}
			else if (fakeLobbyInfos.contains(pchKey))
			{
				return fakeLobbyInfos.at(pchKey).c_str();
			}
		}

		return nullptr;
		//return Components::Party::GetLobbyInfo(steamIDLobby, pchKey);
	}

	bool Matchmaking::SetLobbyData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue)
	{
		/*OutputDebugStringA("{\"");
		OutputDebugStringA(pchKey);
		OutputDebugStringA("\", \"");
		OutputDebugStringA(pchValue);
		OutputDebugStringA("\"},");
		OutputDebugStringA("\n");*/
		return true;
	}

	int Matchmaking::GetLobbyDataCount(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Matchmaking::GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize, char* pchValue, int cchValueBufferSize)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	bool Matchmaking::DeleteLobbyData(CSteamID steamIDLobby, const char* pchKey)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	const char* Matchmaking::GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char* pchKey)
	{
		DUMP_FUNC_NAME();
		return "";
	}

	void Matchmaking::SetLobbyMemberData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue)
	{
		DUMP_FUNC_NAME();
	}

	bool Matchmaking::SendLobbyChatMsg(CSteamID steamIDLobby, const void* pvMsgBody, int cubMsgBody)
	{
		DUMP_FUNC_NAME();
		return true;
	}

	int Matchmaking::GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID* pSteamIDUser, void* pvData, int cubData, EChatEntryType* peChatEntryType)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Matchmaking::RequestLobbyData(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();

		LobbyDataUpdate_t data{};

		const Proxima::Networking::HostedLobby* lobby;
		if (Proxima::Networking::GetFakeJoinOnlyLobby(OUT lobby))
		{
			data.m_bSuccess = true;
			data.m_ulSteamIDLobby = steamIDLobby.m_unAll64Bits;
			data.m_ulSteamIDMember = steamIDLobby.m_unAll64Bits;
		}

		Steam::callbacks->GetClient()->AddCallbackResult(data.k_iCallback, &data, sizeof(data));

		return true;
	}

	void Matchmaking::SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
	{
		DUMP_FUNC_NAME();
	}

	bool Matchmaking::GetLobbyGameServer(CSteamID steamIDLobby, uint32* punGameServerIP, uint16* punGameServerPort, CSteamID* psteamIDGameServer)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	bool Matchmaking::SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers)
	{
		DUMP_FUNC_NAME();
		return true;
	}

	int Matchmaking::GetLobbyMemberLimit(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Matchmaking::SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType)
	{
		DUMP_FUNC_NAME();
		return true;
	}

	bool Matchmaking::SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable)
	{
		DUMP_FUNC_NAME();
		return true;
	}

	CSteamID Matchmaking::GetLobbyOwner(CSteamID steamIDLobby)
	{
		DUMP_FUNC_NAME();
		return SteamUser()->GetSteamID();
	}

	bool Matchmaking::SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner)
	{
		DUMP_FUNC_NAME();
		return true;
	}
}

STEAM_IGNORE_WARNINGS_END
