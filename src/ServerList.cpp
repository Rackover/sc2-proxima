#include "pch.h"

namespace Proxima
{
	std::vector<ServerList::ServerData> ServerList::mockServers{};
	std::mutex ServerList::mutex;

	std::vector< Steam::Steam_Matchmaking_Request*> ServerList::matchmakingRequests{};
	std::vector< Steam::Steam_Matchmaking_Servers_Direct_IP_Request*> ServerList::rulesRequests{};

	HServerListRequest ServerList::nextRequestId = 1;

	void ServerList::ProcessRequest(Steam::Steam_Matchmaking_Request* request)
	{
		for (size_t i = 0; i < mockServers.size(); i++)
		{
			Steam::Steam_Matchmaking_Servers_Gameserver server{};
			server.last_recv = std::chrono::high_resolution_clock::now();
			server.server.id = i + 1;
			server.server.ip = mockServers[i].item.m_NetAdr.GetIP();
			server.server.port = mockServers[i].item.m_NetAdr.GetConnectionPort();

			request->gameservers_filtered.push_back(server);
			request->callbacks->ServerResponded(request->id, i + 1);
		}

		request->completed = true;
		request->callbacks->RefreshComplete(request->id, Steam::EMatchMakingServerResponse::eServerResponded);
		delete request;
	}

	gameserveritem_t* ServerList::GetServerInfo(HServerListRequest requestId, int id)
	{
		Logger::Print("Getting server info for server {} (out of {} mock servers)", id, mockServers.size());
		return &mockServers[id - 1].item;
	}

	void ServerList::ProcessRequest(Steam::Steam_Matchmaking_Servers_Direct_IP_Request* request)
	{
		for (const auto& server : mockServers)
		{
			if (server.item.m_NetAdr.GetIP() == request->ip && server.item.m_NetAdr.GetQueryPort() == request->port)
			{
				for (const auto& kv : server.rules)
				{
					request->rules_response->RulesResponded(kv.first.data(), kv.second.data());
				}

				Logger::Print("Responded with server rules for ip {} and port {}", request->ip, request->port);
				request->rules_response->RulesRefreshComplete();

				delete request;
				return;
			}
		}

		Logger::Print("No server on ip:port {}:{} in server list ({})", request->ip, request->port, mockServers.size());
	}


	void ServerList::AddRequestToQueue(Steam::Steam_Matchmaking_Request* request)
	{
		matchmakingRequests.push_back(request);
	}

	void ServerList::AddRequestToQueue(Steam::Steam_Matchmaking_Servers_Direct_IP_Request* request)
	{
		rulesRequests.push_back(request);
	}

	void ServerList::RunFrame()
	{
		while (matchmakingRequests.size() > 0)
		{
			Steam::Steam_Matchmaking_Request* request = matchmakingRequests.front();

			ProcessRequest(request);

			matchmakingRequests.erase(matchmakingRequests.begin());
		}

		while (rulesRequests.size() > 0)
		{
			auto* request = rulesRequests.front();

			ProcessRequest(request);

			rulesRequests.erase(rulesRequests.begin());
		}
	}

}