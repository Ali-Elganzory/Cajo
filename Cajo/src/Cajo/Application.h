#pragma once

#include "Core.h"

#include "Window.h"
#include "Cajo/LayerStack.h"
#include "Cajo/Events/Event.h"
#include "Cajo/Events/ApplicationEvent.h"


namespace Cajo {

	class CAJO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be defined by Client
	Application* CreateApplication();

}

