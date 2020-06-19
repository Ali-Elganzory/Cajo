#include "cajopch.h"

#include "Shader.h"

#include <glad/glad.h>

namespace Cajo {

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
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

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

}