#include "cajopch.h"

#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cajo {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
			case RendererAPI::OpenGL:    return new OpenGLVertexBuffer(vertices, size);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::OpenGL:    return new OpenGLIndexBuffer(indices, size);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}