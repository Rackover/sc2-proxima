#pragma once
namespace Proxima
{
	enum StatsCategory : uint8_t;

	class FileSystem
	{
	public:
		static bool WriteRemoteStorageFile(const char* name, const char* data, uint32_t length)
		{
			CreateRemoteStorageFolder();
			std::string buffer(data, length);
			return WriteFileInternal(buffer, REMOTE_STORAGE_DIRECTORY_NAME / name);
		}

		static std::string ReadRemoteStorageFile(const char* name, uint32_t maxLength)
		{
			CreateRemoteStorageFolder();
			const auto path = REMOTE_STORAGE_DIRECTORY_NAME / name;
			std::string readBuffer = ReadFileInternal(path);

			return readBuffer.substr(0, min(readBuffer.size(), maxLength));
		}

		static int32 GetRemoteStorageFileSize(const char* name)
		{
			CreateRemoteStorageFolder();
			const auto path = REMOTE_STORAGE_DIRECTORY_NAME / name;

			return static_cast<int32>(GetFileSize(path));
		}

		static bool ReadStats(StatsCategory channel, OUT std::map<std::string, float>& out);

		static bool WriteStats(StatsCategory channel, const std::map<std::string, float>& in);
		static bool ReadProfile(OUT Profile& name);
		static bool WriteProfile(const Profile& name);

	private:
		static const std::filesystem::path BASE_PATH;
		static const std::filesystem::path STATS_DIRECTORY_NAME;
		static const std::filesystem::path STATS_USER_FILENAME;
		static const std::filesystem::path STATS_SERVER_FILENAME;
		static const std::filesystem::path REMOTE_STORAGE_DIRECTORY_NAME;
		static const std::filesystem::path PLAYER_DATA_FILENAME;

		static void CreateStatsFolder();
		static void CreateRemoteStorageFolder();
		static bool WriteFileInternal(const std::string& data, const std::filesystem::path& path);
		static std::string ReadFileInternal(const std::filesystem::path& path);
		static std::streamoff GetFileSize(const std::filesystem::path& path);
	};
}