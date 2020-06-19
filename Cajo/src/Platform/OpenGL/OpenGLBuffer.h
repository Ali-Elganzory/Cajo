#pragma once

#include "Cajo/Renderer/Buffer.h"

namespace Cajo {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}