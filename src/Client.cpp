#include "pch.h"

namespace Proxima
{
	std::vector<std::function<void()>> Client::frameQueue{};
	Profile Client::profile{};
	std::mutex Client::mutex;

	void Client::RunFrame()
	{
		std::lock_guard<std::mutex> _(mutex);
		
		for (const auto& f : frameQueue)
		{
			f();
		}

		frameQueue.clear();
		
		std::lock_guard<std::recursive_mutex> lock(Steam::globalMutex);
		Steam::callbacks->GetResultsClient()->RunCallResults();
		Steam::callbacks->GetClient()->RunCallbacks();
	}

	void Client::AddToQueue(const std::function<void()>& func)
	{
		std::lock_guard<std::mutex> _(mutex);
		frameQueue.push_back(func);
	}

	void Client::InitializeInternal()
	{
		if (FileSystem::ReadProfile(profile))
		{
			Logger::Print("Read proxima profile successfully");
		}
		else 
		{
			profile = Profile::MakeDefaultProfile();

			FileSystem::WriteProfile(profile);
		}

		Stats::GetServer()->Read();
		Stats::GetUser()->Read();


		Logger::Print("Client initialized - profile name {} and ID {} (account {})\n", profile.name, profile.steamID.m_unAll64Bits, static_cast<unsigned int>(profile.steamID.m_comp.m_unAccountID));
	}

#if DEBUG
	void OnMainMenuEventPrintHook(const char* name)
	{
		OutputDebugStringA(name);
		OutputDebugStringA("\n");
	}


	__declspec(naked) void OnMainMenuEventPrint()
	{
		_asm
		{
			pushad
			push edx
			call OnMainMenuEventPrintHook
			add esp, 4
			popad

			// original code
			mov eax, 0x405770
			call eax

			// return to original location
			push 0xB27346
			retn
		}
	}
#endif


	void Client::Initialize()
	{
		// Remove Client voice registration (crashes host for some reason)
		// TODO: Investigate why this crashes and see if there's a way to pass Voice Data through the NET LAN adapter
		Utils::Hook::Nop(0xA9AE73, 23);

		// Proxima version string
		static const auto proximaVersionStringFmt = "Proxima %s %1.3f";
		Utils::Hook::Set(0xC58E64 + 1, proximaVersionStringFmt);

#if DEBUG
		// Allow multiple concurrent processes - this makes development easier
		Utils::Hook::Nop(0XC9B4F3, 1);
		Utils::Hook::Set<uint8>(0XC9B4F3 + 1, 0xE9);

		Utils::Hook(0xB27341, OnMainMenuEventPrint, HOOK_JUMP).install()->quick();
#endif

		Networking::Initialize();
		Client::InitializeInternal();
	}
}