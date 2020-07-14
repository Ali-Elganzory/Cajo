#pragma once

namespace Cajo {

	class GraphicsContext 
	{
	public:
		static Scope<GraphicsContext> Create(void* window);

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}
