#include <Cajo.h>
#include <Cajo/Core/EntryPoint.h>

//#include "ExampleLayer.h"
//#include "Example2DLayer.h"

#include "Encircled.h"

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
		PushLayer(new Encircled("Encircled"));
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