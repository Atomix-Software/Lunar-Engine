#pragma once

#include "luna/renderer/Framebuffer.h"

namespace luna
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& bufferSpecs);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;
		
		inline virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		inline virtual const FramebufferSpecs& GetSpecification() const override { return m_Specifications;  }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;

		FramebufferSpecs m_Specifications;
	};
}