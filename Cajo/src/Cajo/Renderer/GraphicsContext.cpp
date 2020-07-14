#include "cajopch.h"
#include "GraphicsContext.h"

#include "Cajo/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Cajo {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}