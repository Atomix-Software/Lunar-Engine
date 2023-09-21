#include <lnapch.h>

#include "Renderer.h"
#include "Renderer2D.h"

#include "platform/opengl/OpenGLShader.h"

namespace luna
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData();

	void Renderer::Init()
	{
		LNA_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Push(const Shared<Shader>& shader, const Shared<VertexArray>& vao, const glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vao->Bind();
		RenderCommand::DrawIndex(vao);
	}
}