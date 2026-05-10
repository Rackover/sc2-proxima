#include "pch.h"

STEAM_IGNORE_WARNINGS_START

namespace Steam
{
	const char *Friends::GetPersonaName()
	{
		DUMP_FUNC_NAME();
		return Proxima::Client::GetName();
	}

	EPersonaState Friends::GetPersonaState()
	{
		DUMP_FUNC_NAME();
		return EPersonaState::k_EPersonaStateOnline;
	}

	int Friends::GetFriendCount(EFriendFlags eFriendFlags)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	CSteamID Friends::GetFriendByIndex(int iFriend, int iFriendFlags)
	{
		DUMP_FUNC_NAME();
		return CSteamID();
	}

	EFriendRelationship Friends::GetFriendRelationship(CSteamID steamIDFriend)
	{
		DUMP_FUNC_NAME();
		return EFriendRelationship::k_EFriendRelationshipNone;
	}

	EPersonaState Friends::GetFriendPersonaState(CSteamID steamIDFriend)
	{
		DUMP_FUNC_NAME();
		return EPersonaState::k_EPersonaStateOnline;
	}

	const char *Friends::GetFriendPersonaName(CSteamID steamIDFriend)
	{
		DUMP_FUNC_NAME();

		if (steamIDFriend.m_comp.m_unAccountID == Proxima::Client::GetSteamID().m_comp.m_unAccountID)
		{
			return Proxima::Client::GetName();
		}

		return "aaa";
	}

	int Friends::GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Friends::GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t* pFriendGameInfo)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	const char *Friends::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		DUMP_FUNC_NAME();
		return "";
	}

	bool Friends::HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	int Friends::GetClanCount()
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	CSteamID Friends::GetClanByIndex(int iClan)
	{
		DUMP_FUNC_NAME();
		return CSteamID();
	}

	const char *Friends::GetClanName(CSteamID steamIDClan)
	{
		DUMP_FUNC_NAME();
		return "SC2";
	}

	int Friends::GetFriendCountFromSource(CSteamID steamIDSource)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	CSteamID Friends::GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend)
	{
		DUMP_FUNC_NAME();
		return CSteamID();
	}

	bool Friends::IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	void Friends::SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
	{
		DUMP_FUNC_NAME();
	}

	void Friends::ActivateGameOverlay(const char *pchDialog)
	{
		DUMP_FUNC_NAME();
	}

	void Friends::ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID)
	{
		DUMP_FUNC_NAME();
	}

	void Friends::ActivateGameOverlayToWebPage(const char *pchURL)
	{
		DUMP_FUNC_NAME();
	}

	void Friends::ActivateGameOverlayToStore(AppId_t nAppID)
	{
		DUMP_FUNC_NAME();
	}

	void Friends::SetPlayedWith(CSteamID steamIDUserPlayedWith)
	{
		DUMP_FUNC_NAME();
	}
}

STEAM_IGNORE_WARNINGS_END
