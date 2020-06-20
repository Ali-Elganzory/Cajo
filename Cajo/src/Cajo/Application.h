#pragma once

#include "Core.h"

#include "Window.h"
#include "Cajo/LayerStack.h"
#include "Cajo/Events/Event.h"
#include "Cajo/Events/ApplicationEvent.h"

#include "Cajo/ImGui/ImGuiLayer.h"

#include "Cajo/Renderer/Shader.h"
#include "Cajo/Renderer/Buffer.h"
#include "Cajo/Renderer/VertexArray.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

	private:
		static Application* s_Instance;
	};

	// To be defined by Client
	Application* CreateApplication();

}

