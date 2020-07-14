#include "cajopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Cajo {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CAJO_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CAJO_CORE_ASSERT(status, "Couldn't initialize Glad!");

		CAJO_CORE_INFO("OpenGL Specs:");
		CAJO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CAJO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CAJO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
