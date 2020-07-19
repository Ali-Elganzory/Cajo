#pragma once

#include "Core.h"

#include "Cajo/Core/Window.h"
#include "Cajo/Core/LayerStack.h"
#include "Cajo/Core/Timestep.h"

#include "Cajo/Events/Event.h"
#include "Cajo/Events/ApplicationEvent.h"

#include "Cajo/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Cajo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined by Client
	Application* CreateApplication();

}

