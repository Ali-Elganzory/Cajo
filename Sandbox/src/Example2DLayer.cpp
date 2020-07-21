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
	m_CheckboardTexture = Cajo::Texture2D::Create("assets/textures/checker_board.png");
	m_AvarisLogoTexture = Cajo::Texture2D::Create("assets/textures/avaris_logo.png");
}

void Example2DLayer::OnDetach()
{
}

void Example2DLayer::OnUpdate(Cajo::Timestep ts)
{
	CAJO_PROFILE_FUNCTION();

	//	OnUpdate
	{
		CAJO_PROFILE_SCOPE("Camera Update");
		m_CameraController.OnUpdate(ts);
	}

	//	Render
	{
		CAJO_PROFILE_SCOPE("Renderer Prep");

		Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cajo::RenderCommand::Clear();
	}

	int i = 0;

	{
		CAJO_PROFILE_SCOPE("Renderer Draw 20 x 20 Quads");

		Cajo::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for ( ; i < 25; ++i)
			for (int j = 0; j < 100; ++j)
				Cajo::Renderer2D::DrawQuad({ 1.5f * j, 1.5f * i, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.4f, 1.0f });
		for ( ; i < 50; ++i)
			for (int j = 0; j < 100; ++j)
				Cajo::Renderer2D::DrawQuad({ 1.5f * j, 1.5f * i, 0.0f }, { 1.0f, 1.0f }, m_CheckboardTexture);
		/*for (; i < 15; ++i)
			for (int j = 0; j < 20; ++j)
				Cajo::Renderer2D::DrawRotatedQuad({ 1.5f * j, 1.5f * i, 0.0f }, { 1.0f, 1.0f }, 0.785398f, { 0.8f, 0.2f, 0.4f, 1.0f });
		for (; i < 20; ++i)
			for (int j = 0; j < 20; ++j)
				Cajo::Renderer2D::DrawRotatedQuad({ 1.5f * j, 1.5f * i, 0.0f }, { 1.0f, 1.0f }, 0.785398f, m_CheckboardTexture);*/
		Cajo::Renderer2D::EndScene();
	}
}

void Example2DLayer::OnImGuiRender()
{
	{
		CAJO_PROFILE_SCOPE("OnImGuiRender");

		ImGui::Begin("Checker Board Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
}

void Example2DLayer::OnEvent(Cajo::Event& event)
{
	m_CameraController.OnEvent(event);
}
