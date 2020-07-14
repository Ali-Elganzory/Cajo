#pragma once

#include "Cajo/Core/Core.h"

#ifdef CAJO_PLATFORM_WINDOWS

extern Cajo::Application* Cajo::CreateApplication();

int main(int argc, char** argv)
{
	Cajo::Log::Init();
	CAJO_CORE_WARN("Cajo is initialized.");
	CAJO_INFO("Hi there!");

	auto app = Cajo::CreateApplication();
	app->Run();
	delete app;
}

#endif