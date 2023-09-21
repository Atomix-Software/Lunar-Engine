#pragma once

#include "Shader.h"
#include "RenderCmd.h"
#include "OrthoCamera.h"

namespace luna
{
	class LNA_API Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Push(const Shared<Shader>& shader, const Shared<VertexArray>& vao, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
