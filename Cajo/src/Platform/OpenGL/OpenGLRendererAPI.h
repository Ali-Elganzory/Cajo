#pragma once

#include "Cajo/Renderer/RendererAPI.h"

namespace Cajo {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray> vertexArray) override;
	};

}