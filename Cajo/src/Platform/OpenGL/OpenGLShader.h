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

		virtual void UploadUniformMat4(const std::string& uniform, const glm::mat4& mat4) override;

	private:
		uint32_t m_RendererID;
	};

}