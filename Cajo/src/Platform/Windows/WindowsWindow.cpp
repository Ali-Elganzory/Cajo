#include "cajopch.h"

#include "WindowsWindow.h"

#include "Cajo/Events/ApplicationEvent.h"
#include "Cajo/Events/MouseEvent.h"
#include "Cajo/Events/KeyEvent.h"

#include <Glad/glad.h>

namespace Cajo {

	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int errcode, const char* error)
	{
		CAJO_CORE_ERROR("GLFW error {0}: {1}", errcode, error);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		CAJO_CORE_INFO("Creating window {0}: ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: terminate glfw on system shutdown
			int success = glfwInit();
			CAJO_CORE_ASSERT(success, "Couldn't initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CAJO_CORE_ASSERT(status, "Couldn't initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer (window));
				
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow * window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window, int key, int action, int mods)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				default:
					break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow * window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}