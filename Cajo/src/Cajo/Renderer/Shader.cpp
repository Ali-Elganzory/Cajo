#include "cajopch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Cajo {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLShader>(filepath);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

}