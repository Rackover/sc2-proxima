#pragma once

typedef void(*gpg_LogF_t)(const char* fmt, ...);
extern gpg_LogF_t gpg_LogF;

class Logger
{
public:
	static void PrintInternal(const std::string_view& fmt, std::format_args&& args);

	static void Print(const std::string_view& fmt)
	{
		PrintInternal(fmt, std::make_format_args());
	}

	template <typename... Args>
	static void Print(const std::string_view& fmt, Args&&... args)
	{
		PrintInternal(fmt, std::make_format_args(args...));
	}

private:
	static void MessagePrint(const std::string& msg);
	static void PrintOnGameConsole(const std::string& wmsg);
};

#ifdef DEBUG
#define DUMP_FUNC_NAME() { Logger::Print("At {} - called API {}:{} {}", std::time(NULL),  __FILE__, __FUNCTION__, __LINE__); }
#else
#define DUMP_FUNC_NAME()
#endif