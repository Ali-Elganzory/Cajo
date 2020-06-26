#include "cajopch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Cajo {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_Path(filepath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
		CAJO_CORE_ASSERT(data, "Failed to load image!");

		m_Width = width;
		m_Height = height;

		GLenum fileFormat = 0, dataFormat = 0;
		if (channels == 3)
		{
			fileFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4)
		{
			fileFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, fileFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}
