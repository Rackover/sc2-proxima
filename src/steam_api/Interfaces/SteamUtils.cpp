#include "pch.h"

STEAM_IGNORE_WARNINGS_START

namespace Steam
{
	unsigned int Utils::GetSecondsSinceAppActive()
	{
		DUMP_FUNC_NAME();
		//return Game::Sys_Milliseconds() / 1000;
		return 0;
	}

	unsigned int Utils::GetSecondsSinceComputerActive()
	{
		DUMP_FUNC_NAME();
		//return timeGetTime();
		return 0;
	}

	EUniverse Utils::GetConnectedUniverse()
	{
		DUMP_FUNC_NAME();
		return EUniverse::k_EUniversePublic;
	}

	unsigned int Utils::GetServerRealTime()
	{
		DUMP_FUNC_NAME();
		uint32 server_time = std::chrono::duration_cast<std::chrono::duration<uint32>>(std::chrono::system_clock::now().time_since_epoch()).count();
		return server_time;
	}

	const char* Utils::GetIPCountry()
	{
		DUMP_FUNC_NAME();
		return "US";
	}

	bool Utils::GetImageSize(int iImage, uint32* pnWidth, uint32* pnHeight)
	{
		DUMP_FUNC_NAME();

		// Supreme commander 2 developers forgot to check the return value here and use width & height as valid
		// So we have to at least set them to zero
		*pnWidth = 0;
		*pnHeight = 0;
		
		
		return false;
	}

	bool Utils::GetImageRGBA(int iImage, uint8* pubDest, int nDestBufferSize)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	bool Utils::GetCSERIPPort(uint32* unIP, uint16* usPort)
	{
		DUMP_FUNC_NAME();
		return false;
	}

	unsigned char Utils::GetCurrentBatteryPower()
	{
		DUMP_FUNC_NAME();
		return 255;
	}

	unsigned int Utils::GetAppID()
	{
		DUMP_FUNC_NAME();
		return SUPCOM2_APPID;
	}

	void Utils::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
	{
		//Proxy::SetOverlayNotificationPosition(eNotificationPosition);
	}

	bool Utils::IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool* pbFailed)
	{
		DUMP_FUNC_NAME();

		//return true; // Goldberg does it like that
		// but it's dumb

		return Steam::callbacks->GetResultsClient()->HasCompleted(hSteamAPICall);
	}

	ESteamAPICallFailure Utils::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
	{
		DUMP_FUNC_NAME();
		if (hSteamAPICall == 0)
		{
			Logger::Print("Returning CallFailure NetworkFailure on API call zero");
			return ESteamAPICallFailure::k_ESteamAPICallFailureNetworkFailure;
		}

		return ESteamAPICallFailure::k_ESteamAPICallFailureNone;
	}

	bool Utils::GetAPICallResult(SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
	{
		Logger::Print("Trying to get api call result for call {}", hSteamAPICall);

		if (Steam::callbacks->GetResultsClient()->GrabResult(hSteamAPICall, pCallback, cubCallback)) {
			if (pbFailed) *pbFailed = false;
			Logger::Print("GetAPICallResult Succeeded\n");
			return true;
		}
		else {
			memset(pCallback, 0, cubCallback); // Zero out result
			return false;
		}
	}

	void Utils::RunFrame()
	{
		// Deprecated, unused on goldberg
	}

	unsigned int Utils::GetIPCCallCount()
	{
		DUMP_FUNC_NAME();
		return 0;
	}

	void Utils::SetWarningMessageHook(SteamAPIWarningMessageHook_t)
	{
		DUMP_FUNC_NAME();
	}

	bool Utils::IsOverlayEnabled()
	{
		DUMP_FUNC_NAME();
		return false;
	}

	bool Utils::BOverlayNeedsPresent()
	{
		DUMP_FUNC_NAME();
		return false;
	}

	SteamAPICall_t Utils::CheckFileSignature(const char* szFileName)
	{
		DUMP_FUNC_NAME();
		return SteamAPICall_t();
	}

	bool Utils::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax)
	{
		DUMP_FUNC_NAME();
		return false;
	}
	unsigned int Utils::GetEnteredGamepadTextLength()
	{
		DUMP_FUNC_NAME();
		return 0;
	}
	bool Utils::GetEnteredGamepadTextInput(char* pchText, uint32 cchText)
	{
		DUMP_FUNC_NAME();
		return false;
	}
}

STEAM_IGNORE_WARNINGS_END
