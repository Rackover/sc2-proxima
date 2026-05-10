namespace Steam
{

	typedef uint64 SteamLeaderboard_t;
	typedef uint64 SteamLeaderboardEntries_t;
	typedef uint64 UGCHandle_t;

	enum ELeaderboardDataRequest
	{
		k_ELeaderboardDataRequestGlobal = 0,
		k_ELeaderboardDataRequestGlobalAroundUser = 1,
		k_ELeaderboardDataRequestFriends = 2,
		k_ELeaderboardDataRequestUsers = 3
	};

	// the sort order of a leaderboard
	enum ELeaderboardSortMethod
	{
		k_ELeaderboardSortMethodNone = 0,
		k_ELeaderboardSortMethodAscending = 1,	// top-score is lowest number
		k_ELeaderboardSortMethodDescending = 2,	// top-score is highest number
	};

	// the display type (used by the Steam Community web site) for a leaderboard
	enum ELeaderboardDisplayType
	{
		k_ELeaderboardDisplayTypeNone = 0,
		k_ELeaderboardDisplayTypeNumeric = 1,			// simple numerical score
		k_ELeaderboardDisplayTypeTimeSeconds = 2,		// the score represents a time, in seconds
		k_ELeaderboardDisplayTypeTimeMilliSeconds = 3,	// the score represents a time, in milliseconds
	};

	enum ELeaderboardUploadScoreMethod
	{
		k_ELeaderboardUploadScoreMethodNone = 0,
		k_ELeaderboardUploadScoreMethodKeepBest = 1,	// Leaderboard will keep user's best score
		k_ELeaderboardUploadScoreMethodForceUpdate = 2,	// Leaderboard will always replace score with specified
	};
	
#pragma pack( push, 8 )
	struct LeaderboardEntry_t
	{
		CSteamID m_steamIDUser; // user with the entry - use SteamFriends()->GetFriendPersonaName() & SteamFriends()->GetFriendAvatar() to get more info
		int32 m_nGlobalRank;	// [1..N], where N is the number of users with an entry in the leaderboard
		int32 m_nScore;			// score as set in the leaderboard
		int32 m_cDetails;		// number of int32 details available for this entry
		UGCHandle_t m_hUGC;		// handle for UGC attached to the entry
	};

	struct LeaderboardFindResult_t
	{
		enum { k_iCallback = k_iSteamUserStatsCallbacks + 4 };
		SteamLeaderboard_t m_hSteamLeaderboard;	// handle to the leaderboard serarched for, 0 if no leaderboard found
		uint8 m_bLeaderboardFound;				// 0 if no leaderboard found
	};


	//-----------------------------------------------------------------------------
	// Purpose: call result indicating scores for a leaderboard have been downloaded and are ready to be retrieved, returned as a result of DownloadLeaderboardEntries()
	//			use CCallResult<> to map this async result to a member function
	//-----------------------------------------------------------------------------
	struct LeaderboardScoresDownloaded_t
	{
		enum { k_iCallback = k_iSteamUserStatsCallbacks + 5 };
		SteamLeaderboard_t m_hSteamLeaderboard;
		SteamLeaderboardEntries_t m_hSteamLeaderboardEntries;	// the handle to pass into GetDownloadedLeaderboardEntries()
		int m_cEntryCount; // the number of entries downloaded
	};


	struct LeaderboardScoreUploaded_t
	{
		enum { k_iCallback = k_iSteamUserStatsCallbacks + 6 };
		uint8 m_bSuccess;			// 1 if the call was successful
		SteamLeaderboard_t m_hSteamLeaderboard;	// the leaderboard handle that was
		int32 m_nScore;				// the score that was attempted to set
		uint8 m_bScoreChanged;		// true if the score in the leaderboard change, false if the existing score was better
		int m_nGlobalRankNew;		// the new global rank of the user in this leaderboard
		int m_nGlobalRankPrevious;	// the previous global rank of the user in this leaderboard; 0 if the user had no existing entry in the leaderboard
	};

	struct NumberOfCurrentPlayers_t
	{
		enum { k_iCallback = k_iSteamUserStatsCallbacks + 7 };
		uint8 m_bSuccess;			// 1 if the call was successful
		int32 m_cPlayers;			// Number of players currently playing
	};
	
#pragma pack( pop )

	class UserStats
	{
	public:
		// Ask the server to send down this user's data and achievements for this game
		virtual bool RequestCurrentStats();

		// Data accessors
		virtual bool GetStat(const char* pchName, int32* pData);
		virtual bool GetStat(const char* pchName, float* pData);

		// Set / update data
		virtual bool SetStat(const char* pchName, int32 nData);
		virtual bool SetStat(const char* pchName, float fData);
		virtual bool UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength);

		// Achievement flag accessors
		virtual bool GetAchievement(const char* pchName, bool* pbAchieved);
		virtual bool SetAchievement(const char* pchName);
		virtual bool ClearAchievement(const char* pchName);

		// Get the achievement status, and the time it was unlocked if unlocked.
		// If the return value is true, but the unlock time is zero, that means it was unlocked before Steam 
		// began tracking achievement unlock times (December 2009). Time is seconds since January 1, 1970.
		virtual bool GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, uint32* punUnlockTime);

		// Store the current data on the server, will get a callback when set
		// And one callback for every new achievement
		//
		// If the callback has a result of k_EResultInvalidParam, one or more stats 
		// uploaded has been rejected, either because they broke constraints
		// or were out of date. In this case the server sends back updated values.
		// The stats should be re-iterated to keep in sync.
		virtual bool StoreStats();

		// Achievement / GroupAchievement metadata

		// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set. 
		// A return value of 0 may indicate we are still fetching data, and you can wait for the UserAchievementIconReady_t callback
		// which will notify you when the bits are actually read.  If the callback still returns zero, then there is no image set
		// and there never will be.
		virtual int GetAchievementIcon(const char* pchName);
		// Get general attributes (display name / text, etc) for an Achievement
		virtual const char* GetAchievementDisplayAttribute(const char* pchName, const char* pchKey);

		// Achievement progress - triggers an AchievementProgress callback, that is all.
		// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
		virtual bool IndicateAchievementProgress(const char* pchName, uint32 nCurProgress, uint32 nMaxProgress);

		// Friends stats & achievements

		// downloads stats for the user
		// returns a UserStatsReceived_t received when completed
		// if the other user has no stats, UserStatsReceived_t.m_eResult will be set to k_EResultFail
		// these stats won't be auto-updated; you'll need to call RequestUserStats() again to refresh any data
		virtual SteamAPICall_t RequestUserStats(CSteamID steamIDUser);

		// requests stat information for a user, usable after a successful call to RequestUserStats()
		virtual bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData);
		virtual bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData);
		virtual bool GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved);
		// See notes for GetAchievementAndUnlockTime above
		virtual bool GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime);

		// Reset stats 
		virtual bool ResetAllStats(bool bAchievementsToo);

		// Leaderboard functions

		// asks the Steam back-end for a leaderboard by name, and will create it if it's not yet
		// This call is asynchronous, with the result returned in LeaderboardFindResult_t
		virtual SteamAPICall_t FindOrCreateLeaderboard(const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType);

		// as above, but won't create the leaderboard if it's not found
		// This call is asynchronous, with the result returned in LeaderboardFindResult_t
		virtual SteamAPICall_t FindLeaderboard(const char* pchLeaderboardName);

		// returns the name of a leaderboard
		virtual const char* GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard);

		// returns the total number of entries in a leaderboard, as of the last request
		virtual int GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard);

		// returns the sort method of the leaderboard
		virtual ELeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard);

		// returns the display type of the leaderboard
		virtual ELeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard);

		// Asks the Steam back-end for a set of rows in the leaderboard.
		// This call is asynchronous, with the result returned in LeaderboardScoresDownloaded_t
		// LeaderboardScoresDownloaded_t will contain a handle to pull the results from GetDownloadedLeaderboardEntries() (below)
		// You can ask for more entries than exist, and it will return as many as do exist.
		// k_ELeaderboardDataRequestGlobal requests rows in the leaderboard from the full table, with nRangeStart & nRangeEnd in the range [1, TotalEntries]
		// k_ELeaderboardDataRequestGlobalAroundUser requests rows around the current user, nRangeStart being negate
		//   e.g. DownloadLeaderboardEntries( hLeaderboard, k_ELeaderboardDataRequestGlobalAroundUser, -3, 3 ) will return 7 rows, 3 before the user, 3 after
		// k_ELeaderboardDataRequestFriends requests all the rows for friends of the current user 
		virtual SteamAPICall_t DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);

		// Returns data about a single leaderboard entry
		// use a for loop from 0 to LeaderboardScoresDownloaded_t::m_cEntryCount to get all the downloaded entries
		// e.g.
		//		void OnLeaderboardScoresDownloaded( LeaderboardScoresDownloaded_t *pLeaderboardScoresDownloaded )
		//		{
		//			for ( int index; index < pLeaderboardScoresDownloaded->m_cEntryCount; index++ )
		//			{
		//				LeaderboardEntry_t leaderboardEntry;
		//				int32 details[3];		// we know this is how many we've stored previously
		//				GetDownloadedLeaderboardEntry( pLeaderboardScoresDownloaded->m_hSteamLeaderboardEntries, index, &leaderboardEntry, details, 3 );
		//				assert( leaderboardEntry.m_cDetails == 3 );
		//				...
		//			}
		// once you've accessed all the entries, the data will be free'd, and the SteamLeaderboardEntries_t handle will become invalid
		virtual bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax);

		// Uploads a user score to the Steam back-end.
		// This call is asynchronous, with the result returned in LeaderboardScoreUploaded_t
		// Details are extra game-defined information regarding how the user got that score
		// pScoreDetails points to an array of int32's, cScoreDetailsCount is the number of int32's in the list
		virtual SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount);

		// Retrieves the number of players currently playing your game (online + offline)
		// This call is asynchronous, with the result returned in NumberOfCurrentPlayers_t
		virtual SteamAPICall_t GetNumberOfCurrentPlayers();
	};
}