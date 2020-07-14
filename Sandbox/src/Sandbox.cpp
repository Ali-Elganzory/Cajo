#include <Cajo.h>
#include "Cajo/Core/EntryPoint.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Example2DLayer.h"

class ExampleLayer : public Cajo::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer"), m_CameraController((float)(1280.0 / 720.0))
	{
		////////////////////////////////////////////////
		m_VertexArray = Cajo::VertexArray::Create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Cajo::Ref<Cajo::VertexBuffer> vertexBuffer;
		vertexBuffer = Cajo::VertexBuffer::Create(vertices, sizeof(vertices));
		Cajo::BufferLayout layout = {
			{ Cajo::ShaderDataType::Float3, "a_Position" },
			{ Cajo::ShaderDataType::Float2, "a_TextureCoord" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Cajo::Ref<Cajo::IndexBuffer> indexBuffer;
		indexBuffer = Cajo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		////	Sahders & Textures		////
		m_FlatColorShader = Cajo::Shader::Create("assets/shaders/FlatColor.glsl");
		m_TextureShader = Cajo::Shader::Create("assets/shaders/Texture.glsl");

		m_CheckerBoardTexture = Cajo::Texture2D::Create("assets/textures/checker_board.png");
		m_AvarisLogoTexture = Cajo::Texture2D::Create("assets/textures/avaris_logo.png");

		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_Texture", 0);
		////////////////////////////////////////////////
	}

	void OnUpdate(Cajo::Timestep ts) override
	{
		//	OnUpdate
		m_CameraController.OnUpdate(ts);

		//	Render
		Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cajo::RenderCommand::Clear();

		Cajo::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
			for (int x = 0; x < 20; x++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.11f * x, 0.11f * y, 0.0f });
				Cajo::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform * scale);
			}

		m_CheckerBoardTexture->Bind();
		Cajo::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_AvarisLogoTexture->Bind();
		Cajo::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Cajo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Checker Board Settings");
		ImGui::ColorPicker4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Cajo::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Cajo::Ref<Cajo::Shader> m_FlatColorShader;
	Cajo::Ref<Cajo::Shader> m_TextureShader;
	Cajo::Ref<Cajo::VertexArray> m_VertexArray;

	Cajo::Ref<Cajo::Texture2D> m_CheckerBoardTexture;
	Cajo::Ref<Cajo::Texture2D> m_AvarisLogoTexture;

	Cajo::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.4f, 0.2f, 0.6f, 1.0f };
};

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
		PushLayer(new Example2DLayer("Example2DLayer"));
		//PushOverlay(new Cajo::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Cajo::Application* Cajo::CreateApplication()
{
	return new Sandbox();
}