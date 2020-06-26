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

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

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