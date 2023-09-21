#include <lnapch.h>
#include <luna/renderer/TextureAtlas2D.h>

namespace luna
{
	TextureAtlas2D::TextureAtlas2D(const Shared<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) :
		m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}
	Shared<TextureAtlas2D> TextureAtlas2D::CreateFromCoords(const Shared<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		Shared<TextureAtlas2D> result = CreateShared<TextureAtlas2D>(texture, min, max);
		return result;
	}
}