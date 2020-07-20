#include <Cajo.h>
#include <Cajo/Core/EntryPoint.h>

//#include "ExampleLayer.h"
#include "Example2DLayer.h"

#include "Encircled.h"

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
		//PushLayer(new Encircled("Encircled"));
		PushLayer(new Example2DLayer("Example2DLayer"));
	}

	~Sandbox()
	{

	}
};

Cajo::Application* Cajo::CreateApplication()
{
	return new Sandbox();
}