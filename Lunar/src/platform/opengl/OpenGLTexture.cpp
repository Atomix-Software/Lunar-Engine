#include <lnapch.h>
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace luna
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
		m_Width(width), m_Height(height)
	{
		LNA_PROFILE_FUNCTION();
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, bool repeating) :
		m_Path(path)
	{
		LNA_PROFILE_FUNCTION();
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			LNA_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(cons std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		if (data)
		{
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA16;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB16;
				dataFormat = GL_RGB;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;
			LNA_CORE_ASSERT(internalFormat & dataFormat, "Unsupported image format!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			GLenum wrappingFormat = 0;
			if (repeating)
				wrappingFormat = GL_REPEAT;
			else
				wrappingFormat = GL_CLAMP_TO_EDGE;

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, wrappingFormat);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, wrappingFormat);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		LNA_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		LNA_PROFILE_FUNCTION();

		uint32_t bpp = (m_DataFormat == GL_RGBA) ? 4 : 3;
		LNA_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be the whole texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		LNA_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}
}