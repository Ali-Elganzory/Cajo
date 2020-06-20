#pragma once

#include "Cajo/Renderer/Buffer.h"

namespace Cajo {

	class VertexArray {
	public:
		static VertexArray* Create();
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
	};

}