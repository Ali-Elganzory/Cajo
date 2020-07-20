#include "cajopch.h"
#include "Buffer.h"

#include "Cajo/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cajo {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLVertexBuffer>(size);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}