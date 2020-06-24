#pragma once

#include <glm/glm.hpp>

namespace Cajo {

	class Shader 
	{
	public:
		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformInt(const std::string& uniform, const int value) = 0;

		virtual void UploadUniformFloat(const std::string& uniform, const float value) = 0;
		virtual void UploadUniformFloat2(const std::string& uniform, const glm::vec2& value) = 0;
		virtual void UploadUniformFloat3(const std::string& uniform, const glm::vec3& value) = 0;
		virtual void UploadUniformFloat4(const std::string& uniform, const glm::vec4& value) = 0;

		virtual void UploadUniformMat3(const std::string& uniform, const glm::mat3& value) = 0;
		virtual void UploadUniformMat4(const std::string& uniform, const glm::mat4& value) = 0;
	};

}