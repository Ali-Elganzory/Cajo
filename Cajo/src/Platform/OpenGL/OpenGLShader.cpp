#include "cajopch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cajo {

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = Preprocess(source);
		Compile(shaderSources);

		//	Name extraction from filepath
		auto postLastSlash = filepath.find_last_of("/\\");
		postLastSlash = postLastSlash == std::string::npos ? 0 : postLastSlash + 1;
		auto firstDot = filepath.find('.', 0);
		auto length = firstDot == std::string::npos ? (filepath.size() - postLastSlash) : (firstDot - postLastSlash);
		m_Name = filepath.substr(postLastSlash, length);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
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

	std::string OpenGLShader::ReadFile(const std::string& filepath) const
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			CAJO_CORE_ERROR("Could not open a file: \"{0}\"", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source) const
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		GLenum shaderType;

		const char* shaderTypeToken = "#type";
		size_t shaderTypeTokenLength = strlen(shaderTypeToken);
		size_t pos = source.find(shaderTypeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			CAJO_CORE_ASSERT(eol != std::string::npos, "Shader syntax error!");
			size_t begin = pos + shaderTypeTokenLength + 1;
			std::string shaderTypeString = source.substr(begin, eol - begin);

			if (shaderTypeString == "vertex" || shaderTypeString == "Vertex")
				shaderType = GL_VERTEX_SHADER;
			else if (shaderTypeString == "fragment" || shaderTypeString == "Fragment" || shaderTypeString == "pixel" || shaderTypeString == "Pixel")
				shaderType = GL_FRAGMENT_SHADER;
			else
				CAJO_CORE_ASSERT(false, "Unknown shader type!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(shaderTypeToken, nextLinePos);
			shaderSources[shaderType] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> shaderSources)
	{
		GLuint program = glCreateProgram();
		CAJO_CORE_ASSERT(shaderSources.size() <= 2, "Cannot support more than 2 shaders, currently.")
		std::array<GLenum, 2> shadersIDs;

		int shaderIndex = 0;
		for (const auto& kv : shaderSources)
		{
			GLenum shaderType = kv.first;
			const std::string& shaderSource = kv.second;

			GLuint shader = glCreateShader(shaderType);
			const GLchar* source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				CAJO_CORE_ERROR("{0}", infoLog.data());
				CAJO_CORE_ASSERT(false, "Shader compilation error!");

				break;
			}

			glAttachShader(program, shader);
			shadersIDs[shaderIndex++] = shader;
		}

		////		Program Linking		  ////
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
			for (const auto& shader : shadersIDs)
				glDeleteShader(shader);

			CAJO_CORE_ERROR("{0}", infoLog.data());
			CAJO_CORE_ASSERT(false, "Shaders linkage error!");

			return;
		}

		// Always detach shaders after a successful link.
		for (const auto& shader : shadersIDs)
			glDetachShader(program, shader);

		m_RendererID = program;
	}

}