#pragma once
namespace Proxima
{
	class Profile
	{
	public:
		std::string name;
		CSteamID steamID;
		uint16 hostPort;

		static Profile MakeDefaultProfile();

	private:
		static CSteamID GenerateSteamIDFromMacAddress();
		static std::string GetDefaultUsername();

	};

}