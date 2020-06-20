#pragma once

#include "RenderCommand.h"

namespace Cajo {

	class Renderer 
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetCurrentAPI(); };
		inline static void SetCurrentAPI(RendererAPI::API api) { RendererAPI::SetCurrentAPI(api); };
	};

}