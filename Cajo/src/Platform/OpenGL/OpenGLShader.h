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

	private:
		uint32_t m_RendererID;
	};

}