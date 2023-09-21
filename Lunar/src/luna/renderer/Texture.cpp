#include <lnapch.h>
#include "Texture.h"

#include "Renderer.h"
#include "platform/opengl/OpenGLTexture.h"

namespace luna
{
    Shared<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(width, height);
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
    }

    Shared<Texture2D> Texture2D::Create(const std::string& path)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(path);
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
	}
}
