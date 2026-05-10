#pragma once

namespace Proxima
{

	class Client
	{
	public:
		static void Initialize();
		static void RunFrame();
		static void AddToQueue(const std::function<void()>& func);

		static const char* GetName()
		{
			return profile.name.data();
		}

		static CSteamID GetSteamID()
		{
			return profile.steamID;
		}

		static uint16 GetPreferredHostPort()
		{
			return profile.hostPort;
		}

	private:

		static Profile profile;
		static std::mutex mutex;

		static std::vector<std::function<void()>> frameQueue;
	
		static void InitializeInternal();
	};
}