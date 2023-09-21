#pragma once

#include "luna/core/Core.h"
#include <glm/vec2.hpp>

namespace luna
{
	struct FramebufferSpecs
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class LNA_API Framebuffer
	{
	public:
		Framebuffer() = default;
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecs& GetSpecification() const = 0;

		static Shared<Framebuffer> Create(const FramebufferSpecs& bufferSpecs);
	};
}