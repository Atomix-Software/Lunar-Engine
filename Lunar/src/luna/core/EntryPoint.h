#pragma once

#include "luna/core/Core.h"

#ifdef LNA_PLATFORM_WINDOWS
	
extern luna::Application* luna::CreateApplication();

int main(int argc, char* argv[])
{
	luna::Log::Init();

	LNA_PROFILE_BEGIN_SESSION("Startup", "LunaProfile-Startup.json");
	auto game = luna::CreateApplication();
	LNA_PROFILE_END_SESSION();

	LNA_PROFILE_BEGIN_SESSION("Runtime", "LunaProfile-Runtime.json");
	game->Run();
	LNA_PROFILE_END_SESSION();

	LNA_PROFILE_BEGIN_SESSION("Shutdown", "LunaProfile-Shutdown.json");
	delete game;
	LNA_PROFILE_END_SESSION();
	return 0;
}

#endif