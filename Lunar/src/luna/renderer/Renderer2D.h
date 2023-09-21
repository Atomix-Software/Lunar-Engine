#pragma once

#include "luna/core/Core.h"

#include "luna/renderer/Colors.h"
#include "luna/renderer/Texture.h"
#include "luna/renderer/TextureAtlas2D.h"

#include "luna/renderer/Camera.h"
#include "luna/renderer/OrthoCamera.h"

namespace luna
{
	class LNA_API Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = Colors::White);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = Colors::White);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, const glm::vec4& color = Colors::White);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, const glm::vec4& color = Colors::White);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<TextureAtlas2D>& atlas, const glm::vec4& color = Colors::White);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<TextureAtlas2D>& atlas, const glm::vec4& color = Colors::White);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color = Colors::White);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color = Colors::White);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, const glm::vec4& color = Colors::White);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<Texture2D>& texture, const glm::vec4& color = Colors::White);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Shared<TextureAtlas2D>& atlas, const glm::vec4& color = Colors::White);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Shared<TextureAtlas2D>& atlas, const glm::vec4& color = Colors::White);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = Colors::White);
		static void DrawQuad(const glm::mat4& transform, const Shared<Texture2D>& texture, const glm::vec4& color = Colors::White);
		static void DrawQuad(const glm::mat4& transform, const Shared<TextureAtlas2D>& atlas, const glm::vec4& color = Colors::White);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};
}