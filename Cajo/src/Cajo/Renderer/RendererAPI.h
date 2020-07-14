#pragma once

#include "Cajo/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Cajo {

	class RendererAPI 
	{
	public:
		enum class API {
			None = 0, OpenGL = 1
		};

	public:
		static Scope<RendererAPI> Create();

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray> vertexArray) = 0;

		inline static API GetCurrentAPI() { return s_API; }
		inline static void SetCurrentAPI(API api) { s_API = api; };

	private:
		static API s_API;
	};

}