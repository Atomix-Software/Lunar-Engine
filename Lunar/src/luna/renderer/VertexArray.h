#pragma once

#include <memory>

#include "luna/core/Core.h"
#include "luna/renderer/Buffer.h"

namespace luna
{
	class LNA_API VertexArray
	{
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;

		virtual void Bind()   const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(Shared<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(Shared<IndexBuffer>& buffer) = 0;

		virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

		static Shared<VertexArray> Create();
	};
}