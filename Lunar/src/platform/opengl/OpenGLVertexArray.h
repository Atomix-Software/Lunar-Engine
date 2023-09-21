#pragma once

#include <vector>
#include "luna/renderer/VertexArray.h"
#include "luna/renderer/Buffer.h"

namespace luna
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(Shared<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(Shared<IndexBuffer>& buffer) override;

		inline virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		inline virtual const Shared<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;

		std::vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;
	};
}