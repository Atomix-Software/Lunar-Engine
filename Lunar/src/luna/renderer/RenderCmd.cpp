#include <lnapch.h>
#include "RenderCmd.h"

#include "platform/opengl/OpenGLRenderer.h"

namespace luna
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRenderer();
}