#pragma once

#include "Cajo/Renderer/Texture.h"

#include <glad/glad.h>

namespace Cajo {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const uint32_t& width, const uint32_t& height);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void SetData(const void* data, const uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		std::string m_Path;
		uint32_t m_RendererID;

		uint32_t m_Width;
		uint32_t m_Height;

		GLenum m_FileDataFormat, m_DataFormat;
	};

}