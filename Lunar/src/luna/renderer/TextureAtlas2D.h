#pragma once

#include <glm/glm.hpp>
#include <luna/renderer/Texture.h>

namespace luna
{
	class TextureAtlas2D
	{
	public:
		TextureAtlas2D(const Shared<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		
		const Shared<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTextureCoords() const { return m_TexCoords; }

		static Shared<TextureAtlas2D> CreateFromCoords(const Shared<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
	private:
		Shared<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};
}