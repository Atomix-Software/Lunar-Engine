#include "MoonGame.h"
#include <random>

#include "ecs/Components.hpp"
#include "ecs/systems/RenderSystem.h"

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

		m_Engine.AddSystem(new ecs::RenderSystem(m_CamControl));
		m_Engine.Start();

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



	//Ship::Ship(Shared<luna::TextureAtlas2D> texture, entt::registry& registry, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	//{
	//	m_Id = registry.create();
	//	registry.emplace<component::Renderable>(m_Id, texture, 0.1f, 0.1f);
	//	registry.emplace<component::Transform>(m_Id, position, rotation, scale);
	//	registry.emplace<component::Velocity>(m_Id, glm::vec3(0.0f), 0.025f);
	//}
	//
	//void Ship::OnUpdate(Timestep ts)
	//{
	//	auto& trans = registry.get<component::Transform>(m_Id);
	//	auto& motion = registry.get<component::Velocity>(m_Id);
	//
	//	if (Input::IsKeyPressed(LNA_KEY_A))
	//		trans.Rotation.z -= 180.0f * ts;
	//	else if (Input::IsKeyPressed(LNA_KEY_D))
	//		trans.Rotation.z += 180.0f * ts;
	//
	//	if (trans.Rotation.z >= 360.0f)
	//		trans.Rotation.z = 0.0f;
	//	else if (trans.Rotation.z < 0.0f)
	//		trans.Rotation.z = 360.0f;
	//
	//	glm::vec2 velocity(0.0f);
	//	if (Input::IsKeyPressed(LNA_KEY_W))
	//	{
	//		velocity.x = motion.Speed * -glm::cos(glm::radians(trans.Rotation.z));
	//		velocity.y = motion.Speed * glm::sin(glm::radians(trans.Rotation.z));
	//	}
	//	else if (Input::IsKeyPressed(LNA_KEY_S))
	//	{
	//		velocity.x = motion.Speed * glm::cos(glm::radians(trans.Rotation.z));
	//		velocity.y = motion.Speed * -glm::sin(glm::radians(trans.Rotation.z));
	//	}
	//
	//	motion.Direction.x += velocity.x;
	//	motion.Direction.y += velocity.y;
	//
	//	if (motion.Direction.x >= 0.5f)
	//		motion.Direction.x = 0.5f;
	//	else if (motion.Direction.x <= -0.5f)
	//		motion.Direction.x = -0.5f;
	//
	//	if (motion.Direction.y >= 0.5f)
	//		motion.Direction.y = 0.5f;
	//	else if (motion.Direction.y <= -0.5f)
	//		motion.Direction.y = -0.5f;
	//
	//	trans.Position += motion.Direction * glm::vec3(ts, ts, 0.0f);
	//
	//	if (trans.Position.x >= 1.0f || trans.Position.x <= -1.0f)
	//		trans.Position.x = -trans.Position.x;
	//
	//	if (trans.Position.y >= 1.0f || trans.Position.y <= -1.0f)
	//		trans.Position.y = -trans.Position.y;
	//
	//}
	//
	//void Ship::OnRender(Timestep ts)
	//{
	//	auto& trans = registry.get<component::Transform>(m_Id);
	//	auto& spr = registry.get<component::Renderable>(m_Id);
	//
	//	Renderer2D::DrawRotatedQuad(trans.Position, { spr.width * trans.Scale.x, spr.height * trans.Scale.y }, trans.Rotation.z, spr.texture);
	//}
}