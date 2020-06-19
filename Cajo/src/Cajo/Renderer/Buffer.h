#pragma once

namespace Cajo {

	class VertexBuffer {
	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	class IndexBuffer {
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};

}