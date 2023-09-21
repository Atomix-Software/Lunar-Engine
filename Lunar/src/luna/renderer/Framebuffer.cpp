#include <lnapch.h>

#include "luna/renderer/Renderer.h"
#include "luna/renderer/Framebuffer.h"
#include "platform/opengl/OpenGLFramebuffer.h"

namespace luna
{
	Shared<Framebuffer> Framebuffer::Create(const FramebufferSpecs& bufferSpecs)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateShared<OpenGLFramebuffer>(bufferSpecs);
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
	}
}