#include "Example2DLayer.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Example2DLayer::Example2DLayer(const std::string& name)
	: Layer(name), m_CameraController((float)(1280.0 / 720.0), true)
{
}

void Example2DLayer::OnAttach()
{
	m_VertexArray = Cajo::VertexArray::Create();

	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Cajo::Ref<Cajo::VertexBuffer> vertexBuffer = Cajo::VertexBuffer::Create(vertices, sizeof(vertices));
	Cajo::BufferLayout layout = {
		{ Cajo::ShaderDataType::Float3, "a_Position" },
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Cajo::Ref<Cajo::IndexBuffer> indexBuffer = Cajo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_FlatColorShader = Cajo::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Example2DLayer::OnDetach()
{
}

void Example2DLayer::OnUpdate(Cajo::Timestep ts)
{
	//	OnUpdate
	m_CameraController.OnUpdate(ts);

	//	Render
	Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Cajo::RenderCommand::Clear();

	Cajo::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	m_FlatColorShader->Bind();
	m_FlatColorShader->UploadUniformFloat4("u_Color", m_SquareColor);

	Cajo::Renderer::Submit(m_FlatColorShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	Cajo::Renderer::EndScene();
}

void Example2DLayer::OnImGuiRender()
{
	ImGui::Begin("Checker Board Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Example2DLayer::OnEvent(Cajo::Event& event)
{
	m_CameraController.OnEvent(event);
}
