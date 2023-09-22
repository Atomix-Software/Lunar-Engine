#include "MoonGame.h"

namespace luna
{
	Shared<Texture2D> Sheet;

	MoonGame::MoonGame() :
		Layer("MoonGame"), m_CamControl(1280.f, 720.f) {}

	void MoonGame::OnAttach()
	{
		Sheet = Texture2D::Create("assets/textures/stars.png");
		m_Texture = TextureAtlas2D::CreateFromCoords(Sheet, { 3, 0 }, { 16, 16 });
	}

	void MoonGame::OnDetach()
	{
	}

	void MoonGame::OnUpdate(Timestep ts)
	{
		m_CamControl.OnUpdate(ts);

		RenderCommand::SetClearColor({ .1f, .1f, .1f, 1.f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_CamControl.GetCamera());
		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 0.1f, 0.1f }, 0.0f, m_Texture);
		Renderer2D::EndScene();
	}

	void MoonGame::OnEvent(Event& event)
	{
		m_CamControl.OnEvent(event);
	}
}