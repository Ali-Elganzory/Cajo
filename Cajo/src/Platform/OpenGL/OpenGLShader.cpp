#include "cajopch.h"

#include "OpenGLShader.h"

#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cajo {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		////		Vertex Shader		////
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			CAJO_CORE_ERROR("{0}", infoLog.data());
			CAJO_CORE_ASSERT(false, "Vertex shader compilation error!");

			return;
		}

		////		Fragment Shader		////
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shaders anymore.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CAJO_CORE_ERROR("{0}", infoLog.data());
			CAJO_CORE_ASSERT(false, "Fragment shader compilation error!");

			return;
		}

		////		Program Linking		////
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CAJO_CORE_ERROR("{0}", infoLog.data());
			CAJO_CORE_ASSERT(false, "Shaders linkage error!");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& uniform, const int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& uniform, const float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& uniform, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& uniform, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& uniform, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& uniform, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& uniform, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}