#include "cajopch.h"

#include "VertexArray.h"

#include "Cajo/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cajo {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::OpenGL:    return new OpenGLVertexArray();
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}