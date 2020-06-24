#pragma once

#include "Cajo/Renderer/Shader.h"

namespace Cajo {

	class OpenGLShader : public Shader 
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformInt(const std::string& uniform, const int value) override;

		virtual void UploadUniformFloat(const std::string& uniform, const float value) override;
		virtual void UploadUniformFloat2(const std::string& uniform, const glm::vec2& value) override;
		virtual void UploadUniformFloat3(const std::string& uniform, const glm::vec3& value) override;
		virtual void UploadUniformFloat4(const std::string& uniform, const glm::vec4& value) override;

		virtual void UploadUniformMat3(const std::string& uniform, const glm::mat3& value) override;
		virtual void UploadUniformMat4(const std::string& uniform, const glm::mat4& value) override;

	private:
		uint32_t m_RendererID;
	};

}