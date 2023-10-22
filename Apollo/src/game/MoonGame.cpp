#include "MoonGame.h"
#include <random>

#include "ecs/Components.hpp"

#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/PlayerSystem.h"

namespace game
{
	using namespace luna;
	Shared<TextureAtlas2D> Star, SShip;

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
		SShip = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], {0, 0}, {16, 16});

		m_Engine.AddSystem(new ecs::RenderSystem(m_CamControl, 0));
		m_Engine.AddSystem(new ecs::PlayerSystem(1));
		m_Engine.Start();

		auto player = m_Engine.CreateEntity("Player");
		m_Engine.AddComponent<component::Player>(player);
		m_Engine.AddComponent<component::Renderable>(player, SShip, 0.1f, 0.1f);
		m_Engine.AddComponent<component::Transform>(player, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
		m_Engine.AddComponent<component::Velocity>(player, glm::vec3(0.0f), 0.025f);

		for (int i = 0; i < 75; i++)
		{
			auto entity = m_Engine.CreateEntity("Star" + i);
			m_Engine.AddComponent<component::Renderable>(entity, Star, 0.1f, 0.1f);
			m_Engine.AddComponent<component::Transform>(entity, glm::vec3(randf(-1.25, 1.25), randf(-1.25, 1.25), randf(-1.0f, 1.0f)), glm::vec3(0.0f, 0.0f, randf(0.0f, 360.0f)), glm::vec3(1.0f));
		}
	}

	void MoonGame::OnDetach()
	{
		m_Textures.clear();
	}

	void MoonGame::OnUpdate(Timestep ts)
	{
		m_CamControl.OnUpdate(ts);

		m_Engine.OnUpdate(ts);
	}

	void MoonGame::OnEvent(Event& event)
	{
		m_CamControl.OnEvent(event);
	}

}