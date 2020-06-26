#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Cajo {

	class RendererAPI 
	{
	public:
		enum class API {
			None = 0, OpenGL = 1
		};

	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray> vertexArray) = 0;

		inline static API GetCurrentAPI() { return s_API; }
		inline static void SetCurrentAPI(API api) { s_API = api; };

	private:
		static API s_API;
	};

}