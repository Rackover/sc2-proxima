#include "pch.h"

STEAM_IGNORE_WARNINGS_START

namespace Steam
{
	bool Apps::BIsSubscribed() { return true; }
	bool Apps::BIsLowViolence() { return false; }
	bool Apps::BIsCybercafe() { return false; }
	bool Apps::BIsVACBanned() { return false; }
	const char* Apps::GetCurrentGameLanguage() { return ""; }
	const char* Apps::GetAvailableGameLanguages() { return ""; }

	// only use this member if you need to check ownership of another game related to yours, a demo for example

	bool Apps::BIsSubscribedApp(AppId_t appID) { return true; }

	// Takes AppID of DLC and checks if the user owns the DLC & if the DLC is installed

	bool Apps::BIsDlcInstalled(AppId_t appID) { return true; }

	// returns the Unix time of the purchase of the app

	unsigned int Apps::GetEarliestPurchaseUnixTime(AppId_t nAppID) { return 0; }

	// Checks if the user is subscribed to the current app through a free weekend
	// This function will return false for users who have a retail or other type of license
	// Before using, please ask your Valve technical contact how to package and secure your free weekened

	bool Apps::BIsSubscribedFromFreeWeekend() { return false; }

	// Returns the number of DLC pieces for the running app

	int Apps::GetDLCCount() { return 0; }

	// Returns metadata for DLC by index, of range [0, GetDLCCount()]

	bool Apps::BGetDLCDataByIndex(int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize) { return false; }

	// Install/Uninstall control for optional DLC

	void Apps::InstallDLC(AppId_t nAppID) {}
	void Apps::UninstallDLC(AppId_t nAppID) {}

	// Request legacy cd-key for yourself or owned DLC. If you are interested in this
	// data then make sure you provide us with a list of valid keys to be distributed
	// to users when they purchase the game, before the game ships.
	// You'll receive an AppProofOfPurchaseKeyResponse_t callback when
	// the key is available (which may be immediately).

	void Apps::RequestAppProofOfPurchaseKey(AppId_t nAppID) {}
	bool Apps::GetCurrentBetaName(char* pchName, int cchNameBufferSize) {
		DUMP_FUNC_NAME();
		return "public";
	}

	// returns current beta branch name, 'public' is the default branch

	bool Apps::MarkContentCorrupt(bool bMissingFilesOnly) {
		DUMP_FUNC_NAME(); 
		return false;
	}

	// signal Steam that game files seems corrupt or missing

	uint32 Apps::GetInstalledDepots(AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots) {
		DUMP_FUNC_NAME();
		return 0;
	}

	// returns current app install folder for AppID, returns folder name length

	uint32 Apps::GetAppInstallDir(AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize)
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	bool Apps::BIsAppInstalled(AppId_t appID) { return true; }

	CSteamID Apps::GetAppOwner()
	{
		DUMP_FUNC_NAME();
		return Proxima::Client::GetSteamID();
	}

	const char* Apps::GetLaunchQueryParam(const char* pchKey)
	{
		DUMP_FUNC_NAME();
		return nullptr;
	}

	bool Apps::GetDlcDownloadProgress(AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	int Apps::GetAppBuildId()
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	// Returns the associated launch param if the game is run via steam://run/<appid>//?param1=value1;param2=value2;param3=value3 etc.
	// Parameter names starting with the character '@' are reserved for internal use and will always return and empty string.
	// Parameter names starting with an underscore '_' are reserved for steam features -- they can be queried by the game,
	// but it is advised that you not param names beginning with an underscore for your own features.

	// get download progress for optional DLC

	// Request all proof of purchase keys for the calling appid and asociated DLC.
	// A series of AppProofOfPurchaseKeyResponse_t callbacks will be sent with
	// appropriate appid values, ending with a final callback where the m_nAppId
}

STEAM_IGNORE_WARNINGS_END
