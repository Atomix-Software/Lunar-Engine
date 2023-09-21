#pragma once

#include "luna/renderer/Texture.h"

typedef unsigned int GLenum;

namespace luna
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path, bool repeating = false);
		virtual ~OpenGLTexture2D();

		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		
		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		inline virtual bool operator==(const Texture& other) const override { return m_RendererID == other.GetRendererID(); }

	private:
		uint32_t m_RendererID;

		std::string m_Path;
		uint32_t m_Width, m_Height;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
