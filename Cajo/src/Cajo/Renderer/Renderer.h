#pragma once

namespace Cajo {

	enum class RendererAPI 
	{
		None = 0, OpenGL = 1,
	};

	class Renderer {
	public:
		inline static RendererAPI GetCurrentAPI() { return s_RendererAPI; };
		inline static RendererAPI SetCurrentAPI(RendererAPI api) { return s_RendererAPI = api; };

	private:
		static RendererAPI s_RendererAPI;
	};

}