#include "Example2DLayer.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Example2DLayer::Example2DLayer(const std::string& name)
	: Layer(name), m_CameraController((float)(1280.0 / 720.0), true)
{
}

void Example2DLayer::OnAttach()
{
	m_AvarisLogoTexture = Cajo::Texture2D::Create("assets/textures/avaris_logo.png");
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

	Cajo::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Cajo::Renderer2D::DrawQuad({ -0.5f,  0.5f, 0.8 }, { 1.0f, 1.0f }, m_SquareColor);
	Cajo::Renderer2D::DrawQuad({  1.0f, -1.0f, 0.8 }, { 1.5f, 1.5f }, m_SquareColor);
	Cajo::Renderer2D::DrawQuad({  1.5f,  1.5f, 0.5 }, { 4.5f, 4.5f }, { 1.0f,1.0f,1.0f,1.0f });
	Cajo::Renderer2D::DrawQuad({  1.5f,  1.5f, 0.6 }, { 4.5f, 4.5f }, m_AvarisLogoTexture);
	Cajo::Renderer2D::EndScene();
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
