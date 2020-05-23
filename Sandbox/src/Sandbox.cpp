#include <Cajo.h>

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Cajo::Application* Cajo::CreateApplication()
{
	return new Sandbox();
}