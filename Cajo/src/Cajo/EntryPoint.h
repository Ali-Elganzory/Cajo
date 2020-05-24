#pragma once

#ifdef CAJO_PLATFORM_WINDOWS

extern Cajo::Application* Cajo::CreateApplication();

int main(int argc, char** argv)
{
	Cajo::Log::Init();
	CAJO_CORE_WARN("Cajo is initialized.");
	CAJO_INFO("Hi there! {0}", 5);

	auto app = Cajo::CreateApplication();
	app->Run();
	delete app;
}

#endif