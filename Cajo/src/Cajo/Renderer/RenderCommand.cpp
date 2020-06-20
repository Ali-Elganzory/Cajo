#include "cajopch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cajo {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}