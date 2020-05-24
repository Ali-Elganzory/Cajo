#include "Application.h"

#include "Cajo/Events/ApplicationEvent.h"
#include "Cajo/Log.h"

namespace Cajo {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CAJO_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CAJO_TRACE(e);
		}

		while (true);
	}

}