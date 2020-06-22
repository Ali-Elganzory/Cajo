#include "cajopch.h"

#include "Application.h"

#include "Cajo/Log.h"

#include "Cajo/Renderer/Renderer.h"

#include "Input.h"
#include "KeyCodes.h"

namespace Cajo {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		CAJO_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window.reset(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		////////////////////////////////////////////////
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fargmentSource = R"(
			#version 330 core
			
			in vec3 v_Position;
			layout(location = 0) out vec4 color;
			
			void main()
			{
				color = vec4((v_Position + 1) / 2, 1.0);
			}
		)";

		m_Shader.reset(Shader::Create(vertexSource, fargmentSource));
		////////////////////////////////////////////////
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(MoveCamera));
		
		//CAJO_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			//m_Camera.SetPosition({ 0.5f, 0.0f, 0.0f });
			//m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}



	bool Application::MoveCamera(KeyPressedEvent& e)
	{
		switch (e.GetKeyCode())
		{
			case CAJO_KEY_LEFT:  m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({ -0.05f, 0.0f, 0.0f })); return true;
			case CAJO_KEY_RIGHT: m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({ 0.05f, 0.0f, 0.0f })); return true;
			case CAJO_KEY_UP:    m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({ 0.0f, 0.05f, 0.0f })); return true;
			case CAJO_KEY_DOWN:  m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({ 0.0f, -0.05f, 0.0f })); return true;
		}
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}