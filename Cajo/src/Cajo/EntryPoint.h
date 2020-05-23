#pragma once

#ifdef CAJO_PLATFORM_WINDOWS

extern Cajo::Application* Cajo::CreateApplication();

int main(int argc, char** argv)
{
	printf("Cajo is up and running...");

	auto app = Cajo::CreateApplication();
	app->Run();
	delete app;
}

#endif