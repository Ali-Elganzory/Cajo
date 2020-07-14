#include "cajopch.h"
#include "RenderCommand.h"

namespace Cajo {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}