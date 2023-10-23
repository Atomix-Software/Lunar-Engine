#include "MoonGame.h"
#include <random>

#include "ecs/Components.hpp"

#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/PlayerSystem.h"
#include "ecs/systems/MotionSystem.h"

namespace game
{
	std::random_device rd;
	std::mt19937 rng(rd());

	using namespace luna;
	Shared<TextureAtlas2D> Ship;
	Shared<TextureAtlas2D> Rocks[3], Stars[4];

	float randf(float min, float max)
	{
		return  min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

	MoonGame::MoonGame() :
		Layer("MoonGame"), m_CamControl(640.f, 640.f) {}

	void MoonGame::OnAttach()
	{
		m_Engine.AddSystem(new ecs::RenderSystem(m_CamControl, 0));
		m_Engine.AddSystem(new ecs::PlayerSystem(1));
		m_Engine.AddSystem(new ecs::MotionSystem(2));
		m_Engine.Start();

		m_Textures["stars"] = Texture2D::Create("assets/textures/stars.png");
		m_Textures["ship_rocks"] = Texture2D::Create("assets/textures/ship_rocks.png");
		Ship = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], {0, 0}, {16, 16});

		Stars[0] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 0, 0 }, { 16, 16 });
		Stars[1] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 1, 0 }, { 16, 16 });
		Stars[2] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 2, 0 }, { 16, 16 });
		Stars[3] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 3, 0 }, { 16, 16 });

		Rocks[0] = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], { 1, 0 }, { 16, 16 });
		Rocks[1] = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], { 2, 0 }, { 16, 16 });
		Rocks[2] = TextureAtlas2D::CreateFromCoords(m_Textures["ship_rocks"], { 3, 0 }, { 16, 16 });

		std::uniform_int_distribution<int> starGn(1, 4);
		for (int i = 0; i < 75; i++)
		{
			auto starLevel = starGn(rng) - 1;
			auto entity = m_Engine.CreateEntity("Star");
			m_Engine.AddComponent<component::Renderable>(entity, Stars[starLevel], 0.075f, 0.075f);
			m_Engine.AddComponent<component::Transform>(entity, glm::vec3(randf(-1.25, 1.25), randf(-1.25, 1.25), randf(-1.0f, -0.9f)), glm::vec3(0.0f, 0.0f, randf(0.0f, 360.0f)), glm::vec3(1.0f));
		}

		std::uniform_int_distribution<int> levelGn(2, 3);
		for (int i = 0; i < 6; i++)
		{
			auto rock = m_Engine.CreateEntity("Rock");

			float num = randf(-1.0f, 1.0f);
			auto levelNum = levelGn(rng);

			m_Engine.AddComponent<component::Rock>(rock, levelNum, num > 0.0f ? true : false);
			float speed = 0.2f;

			switch (levelNum)
			{
			case 1:
				m_Engine.AddComponent<component::Renderable>(rock, Rocks[2], 0.1f, 0.1f);
				speed = 0.1f;
				break;
			case 2:
				m_Engine.AddComponent<component::Renderable>(rock, Rocks[1], 0.125f, 0.125f);
				speed = 0.1f;
				break;
			case 3:
				m_Engine.AddComponent<component::Renderable>(rock, Rocks[0], 0.15f, 0.15f);
				speed = 0.001f;
				break;
			}

			m_Engine.AddComponent<component::Transform>(rock, glm::vec3(randf(-1.0f, 1.0f), randf(-1.0f, 1.0f), 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
			m_Engine.AddComponent<component::Velocity>(rock, glm::vec3(randf(-0.5f, 0.5f), randf(-0.5f, 0.5f), 0.0f), speed);
		}

		auto player = m_Engine.CreateEntity("Player");
		m_Engine.AddComponent<component::Player>(player);
		m_Engine.AddComponent<component::Renderable>(player, Ship, 0.075f, 0.075f);
		m_Engine.AddComponent<component::Transform>(player, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
		m_Engine.AddComponent<component::Velocity>(player, glm::vec3(0.0f), 0.025f);
	}

	void MoonGame::OnDetach()
	{
		m_Textures.clear();
	}

	void MoonGame::OnUpdate(Timestep ts)
	{
		m_CamControl.OnUpdate(ts);

		if (Input::IsKeyPressed(LNA_KEY_ESCAPE))
		{
			m_Engine.Stop();
			Application::Get().Close();
			return;
		}

		m_Engine.OnUpdate(ts);
	}

	void MoonGame::OnEvent(Event& event)
	{
		m_CamControl.OnEvent(event);
	}

}