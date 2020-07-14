#pragma once

#include "Core.h"

#include "Cajo/Core/Window.h"
#include "Cajo/Core/LayerStack.h"
#include "Cajo/Core/Timestep.h"

#include "Cajo/Events/Event.h"
#include "Cajo/Events/ApplicationEvent.h"

#include "Cajo/ImGui/ImGuiLayer.h"

namespace Cajo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime;

	private:
		static Application* s_Instance;
	};

	// To be defined by Client
	Application* CreateApplication();

}

