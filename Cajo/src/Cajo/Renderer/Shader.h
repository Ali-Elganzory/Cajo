#pragma once

#include <glm/glm.hpp>

namespace Cajo {

	class Shader 
	{
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual void SetInt(const std::string& uniform, const int value) = 0;

		virtual void SetFloat(const std::string& uniform, const float value) = 0;
		virtual void SetFloat2(const std::string& uniform, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& uniform, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& uniform, const glm::vec4& value) = 0;

		virtual void SetMat3(const std::string& uniform, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& uniform, const glm::mat4& value) = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Load(const std::string& filepath);

		Ref<Shader> GetShader(const std::string& name);

	private:
		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}