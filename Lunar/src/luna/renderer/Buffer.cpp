#include <lnapch.h>
#include "Buffer.h"

#include "Renderer.h"

#include "platform/opengl/OpenGLBuffer.h"

namespace luna
{
	Shared<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateShared<OpenGLVertexBuffer>(size);
		}

		LNA_CORE_ASSERT(false, "Unknown Rendering API!");
		return nullptr;
	}

	Shared<VertexBuffer>VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateShared<OpenGLVertexBuffer>(vertices, size);
		}

		LNA_CORE_ASSERT(false, "Unknown Rendering API!");
		return nullptr;
	}

	Shared<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateShared<OpenGLIndexBuffer>(indices, count);
		}

		LNA_CORE_ASSERT(false, "Unknown Rendering API!");
		return nullptr;
	}
}