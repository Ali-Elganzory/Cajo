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

	//	TODO: move into renderer
	Cajo::Ref<Cajo::Shader> m_FlatColorShader;
	Cajo::Ref<Cajo::VertexArray> m_VertexArray;

	glm::vec4 m_SquareColor = { 0.4f, 0.2f, 0.6f, 1.0f };
};