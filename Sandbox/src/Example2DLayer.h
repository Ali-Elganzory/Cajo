#pragma once

#include <Cajo.h>

class Example2DLayer : public Cajo::Layer
{
public:
	Example2DLayer(const std::string& name);
	virtual ~Example2DLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Cajo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Cajo::Event& event) override;

private:
	Cajo::OrthographicCameraController m_CameraController;
	
	Cajo::Ref<Cajo::Texture2D> m_CheckboardTexture;
	Cajo::Ref<Cajo::Texture2D> m_AvarisLogoTexture;

	glm::vec4 m_SquareColor = { 0.4f, 0.2f, 0.6f, 1.0f };
};