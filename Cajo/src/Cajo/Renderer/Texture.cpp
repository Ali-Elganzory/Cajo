#include "cajopch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Cajo {

	Ref<Texture2D> Cajo::Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLTexture2D>(filepath);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}

}

