#pragma once

namespace Steam
{
	// SteamClient009

	class Client
	{
	public:

		// Creates a communication pipe to the Steam client
		virtual HSteamPipe CreateSteamPipe();

		// Releases a previously created communications pipe
		virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe);

		// connects to an existing global user, failing if none exists
		// used by the game to coordinate with the steamUI
		virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe);

		// used by game servers, create a steam user that won't be shared with anyone else
		virtual HSteamUser CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType);

		// removes an allocated user
		virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser);

		// retrieves the Steam::User interface associated with the handle
		virtual Steam::User* GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// retrieves the Steam::GameServer interface associated with the handle
		virtual Steam::GameServer* GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// set the local IP and Port to bind to
		// this must be set before CreateLocalUser()
		virtual void SetLocalIPBinding(uint32 unIP, uint16 usPort);

		// returns the Steam::Friends interface
		virtual Steam::Friends* GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::Utils interface
		virtual Steam::Utils* GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::Matchmaking interface
		virtual Steam::Matchmaking* GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::MasterServerUpdater interface
		virtual /* Steam::MasterServerUpdater */void* GetISteamMasterServerUpdater(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::MatchmakingServers interface
		virtual Steam::MatchmakingServers* GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the a generic interface
		virtual void* GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::UserStats interface
		virtual Steam::UserStats* GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns the Steam::GameServerStats interface
		virtual Steam::GameServerStats* GetISteamGameServerStats(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);

		// returns apps interface
		virtual Steam::Apps* GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// networking
		virtual Steam::Networking* GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);

		// remote storage
		virtual Steam::RemoteStorage* GetISteamRemoteStorage(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);

		// this needs to be called every frame to process matchmaking results
		// redundant if you're already calling SteamAPI_RunCallbacks()
		virtual void RunFrame();

		// returns the number of IPC calls made since the last time this function was called
		// Used for perf debugging so you can understand how many IPC calls your game makes per frame
		// Every IPC call is at minimum a thread context switch if not a process one so you want to rate
		// control how often you do them.
		virtual uint32 GetIPCCallCount();

		// API warning handling
		// 'int' is the severity; 0 for msg, 1 for warning
		// 'const char *' is the text of the message
		// callbacks will occur directly after the API function is called that generated the warning or message
		virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction);
	};
}
