#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace Cajo {

	class Renderer 
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetCurrentAPI(); };
		inline static void SetCurrentAPI(RendererAPI::API api) { RendererAPI::SetCurrentAPI(api); };

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}