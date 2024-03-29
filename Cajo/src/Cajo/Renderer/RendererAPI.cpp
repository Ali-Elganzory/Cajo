#include "cajopch.h"
#include "RendererAPI.h"

#include "Cajo/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cajo {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateScope<OpenGLRendererAPI>();
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}