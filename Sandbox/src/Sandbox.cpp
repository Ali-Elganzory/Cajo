#include <Cajo.h>

class ExampleLayer : public Cajo::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{
	}

	void OnUpdate() override
	{
		if (Cajo::Input::IsKeyPressed(CAJO_KEY_TAB))
			CAJO_TRACE("Tab key is pressed!");
	}

	void OnEvent(Cajo::Event& event) override
	{
		//CAJO_TRACE("{0}", event);
	}
};

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Cajo::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Cajo::Application* Cajo::CreateApplication()
{
	return new Sandbox();
}