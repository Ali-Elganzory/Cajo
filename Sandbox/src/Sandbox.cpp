#include <Cajo.h>

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
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