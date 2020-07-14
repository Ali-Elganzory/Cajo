#include "cajopch.h"
#include "Shader.h"

#include "Cajo/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Cajo {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLShader>(filepath);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:      CAJO_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		CAJO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		CAJO_CORE_ASSERT(!Exists(name), "Duplicate shader name!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto name = shader->GetName();
		CAJO_CORE_ASSERT(!Exists(name), "Duplicate shader name!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		CAJO_CORE_ASSERT(Exists(name), "Shader does not exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}