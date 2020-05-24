#pragma once

#include "Core.h"
#include "Events\Event.h"

namespace Cajo {

	class CAJO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined by Client
	Application* CreateApplication();

}

