#include "lnapch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "platform/opengl/OpenGLVertexArray.h"
#include "platform/opengl/OpenGLBuffer.h"

namespace luna
{

    Shared<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateShared<OpenGLVertexArray>();
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
    }

}