namespace Proxima
{
	struct gpg_ConnectionManager
	{
		char pad[27];
		uint8_t* lobbyStatus;
	};

	class Networking
	{
	public:
		static constexpr uint16_t DEFAULT_PORT = 16010;

		struct HostedLobby
		{
			std::string name;
			uint32_t address;
			uint16_t port;
		};

		static void AddFakeJoinOnlyLobby(const std::string& ipAddress);

		static bool GetFakeJoinOnlyLobby(OUT const HostedLobby*& data);
		static void Initialize();

	private:

		static bool isFakeJoinLobbyAvailable;
		static HostedLobby currentLobby;

		static void SetConnectionAdapterTypeForceUDP();
		static void InjectEndpointIntoConnxHook(uint32 connexionInfo);
		static void InjectEndpointIntoConnx();
		static char __stdcall SetupLanGame_Hook(int a1, int a2, const char* scenarioName, const char* scenarioPath);
	};
}