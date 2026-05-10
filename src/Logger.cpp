#include "pch.h"

gpg_LogF_t gpg_LogF = gpg_LogF_t(0xB7D2B0);


void Logger::PrintInternal(const std::string_view& fmt, std::format_args&& args)
{
	const auto narrowMessage = std::vformat(fmt, args);
	MessagePrint(narrowMessage);
}

void Logger::MessagePrint(const std::string& msg)
{
	std::printf("%s\n", msg.data());
	std::fflush(stdout);

#ifdef _DEBUG
	const std::string withNewLine = msg + "\n";
	OutputDebugString(withNewLine.data());
#endif

	PrintOnGameConsole(msg);
}


void Logger::PrintOnGameConsole(const std::string& msg)
{
	//// Call original print function
	if (!msg.empty())
	{
		// This is the adress of the gameSessionManager, initialized at SCMain AppInit 1
		// If it's present, the logger is ready. It could be ready earlier but I'm not sure how to know
		bool isGameInitializedEnough = *reinterpret_cast<bool*>(0x18F2084);
		if (isGameInitializedEnough) {
			gpg_LogF(msg.c_str());
		}
	}
}


