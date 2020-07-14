#pragma once

#include "Cajo/Renderer/Shader.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Cajo {

	class OpenGLShader : public Shader 
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetInt(const std::string& uniform, const int value) override;

		virtual void SetFloat(const std::string& uniform, const float value) override;
		virtual void SetFloat2(const std::string& uniform, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& uniform, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& uniform, const glm::vec4& value) override;

		virtual void SetMat3(const std::string& uniform, const glm::mat3& value) override;
		virtual void SetMat4(const std::string& uniform, const glm::mat4& value) override;

		//	Upload uniform
		void UploadUniformInt(const std::string& uniform, const int value);

		void UploadUniformFloat(const std::string& uniform, const float value);
		void UploadUniformFloat2(const std::string& uniform, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& uniform, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& uniform, const glm::vec4& value);

		void UploadUniformMat3(const std::string& uniform, const glm::mat3& value);
		void UploadUniformMat4(const std::string& uniform, const glm::mat4& value);

	private:
		std::string ReadFile(const std::string& filepath) const;
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source) const;
		void Compile(std::unordered_map<GLenum, std::string> shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}