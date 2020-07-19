#pragma once

#include "Cajo/Core/Core.h"

#ifdef CAJO_PLATFORM_WINDOWS

extern Cajo::Application* Cajo::CreateApplication();

int main(int argc, char** argv)
{
	Cajo::Log::Init();

	CAJO_PROFILE_BEGIN_SESSION("Startup", "Cajo-Profile-Startup.json");
	auto app = Cajo::CreateApplication();
	CAJO_PROFILE_END_SESSION();

	CAJO_PROFILE_BEGIN_SESSION("Startup", "Cajo-Profile-Runtime.json");
	app->Run();
	CAJO_PROFILE_END_SESSION();

	CAJO_PROFILE_BEGIN_SESSION("Startup", "Cajo-Profile-Shutdown.json");
	delete app;
	CAJO_PROFILE_END_SESSION();

}

#endif