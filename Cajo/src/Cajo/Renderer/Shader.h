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

		virtual void UploadUniformVec4(const std::string& uniform, const glm::vec4& vec4) = 0;
		virtual void UploadUniformMat4(const std::string& uniform, const glm::mat4& mat4) = 0;
	};

}