#pragma once

#include "luna/core/Core.h"
#include "luna/renderer/RendererAPI.h"

namespace luna
{
	class LNA_API RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndex(const Shared<VertexArray>& vao, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vao, indexCount);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}