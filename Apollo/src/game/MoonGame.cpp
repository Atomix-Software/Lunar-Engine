#include "MoonGame.h"

#include <entt.hpp>
#include <random>

namespace game
{
	using namespace luna;

	Shared<TextureAtlas2D> Star, Ship;

	entt::registry registry;

	float randf(float min, float max)
	{
		return  min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

	MoonGame::MoonGame() :
		Layer("MoonGame"), m_CamControl(640.f, 640.f) {}

	void MoonGame::OnAttach()
	{
		srand(time(0));
		m_Textures["stars"] = Texture2D::Create("assets/textures/stars.png");
		m_Textures["ship_rocks"] = Texture2D::Create("assets/textures/ship_rocks.png");

		Star = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], {0, 0}, {16, 16});
		Ship = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], {0, 0}, {16, 16});

		auto entity = registry.create();
		registry.emplace<Component::Renderable>(entity, Ship, 0.1f, 0.1f);
		registry.emplace<Component::Transform>(entity, glm::vec3(0.5f, -0.25f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

		for (int i = 0; i < 50; i++)
		{
			auto entity = registry.create();
			registry.emplace<Component::Renderable>(entity, Star, 0.1f, 0.1f);
			registry.emplace<Component::Transform>(entity, glm::vec3(randf(-1.0f, 1.0f), randf(-1.0f, 1.0f), -0.1f), glm::vec3(0.0f, 0.0f, randf(0.0f, 360.0f)), glm::vec3(1.0f));
		}
	}

	void MoonGame::OnDetach()
	{
		m_Textures.clear();
		registry.clear();
	}

	void MoonGame::OnUpdate(Timestep ts)
	{
		m_CamControl.OnUpdate(ts);
		auto view = registry.view<Component::Renderable, Component::Transform>();

		auto ent = view.back();
		auto& trans = registry.get<Component::Transform>(ent);

		if (Input::IsKeyPressed(LNA_KEY_W))
			trans.Position.y += 0.5f * ts;
		else if (Input::IsKeyPressed(LNA_KEY_S))
			trans.Position.y -= 0.5f * ts;

		if (Input::IsKeyPressed(LNA_KEY_A))
			trans.Rotation.z -= 90.0f * ts;
		else if (Input::IsKeyPressed(LNA_KEY_D))
			trans.Rotation.z += 90.0f * ts;

		RenderCommand::SetClearColor({ .05f, .05f, .05f, 1.f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_CamControl.GetCamera());

		// Rendering every Entity with a Renderable and Transform Component
		for (auto [entity, spr, trans] : view.each())
			Renderer2D::DrawRotatedQuad(trans.Position, { spr.width * trans.Scale.x, spr.height * trans.Scale.y }, trans.Rotation.z, spr.texture);

		Renderer2D::EndScene();
	}

	void MoonGame::OnEvent(Event& event)
	{
		m_CamControl.OnEvent(event);
	}
}