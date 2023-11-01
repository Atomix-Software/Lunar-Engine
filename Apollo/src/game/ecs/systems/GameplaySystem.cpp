#include "GameplaySystem.h"

#include <luna/ecs/EntityEngine.h>
#include "../Components.hpp"

namespace game
{

	entt::entity CreatePlayer(entt::registry& reg, luna::Shared<luna::TextureAtlas2D> texture)
	{
		auto player = reg.create();
		reg.emplace<component::Tag>(player, "Player");
		reg.emplace<component::Player>(player);
		reg.emplace<component::Timer>(player);
		reg.emplace<component::Collision>(player);
		reg.emplace<component::Renderable>(player, texture, 0.075f, 0.075f);
		reg.emplace<component::Transform>(player, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
		reg.emplace<component::Velocity>(player, glm::vec3(0.0f), 0.025f);

		return player;
	}
	
	entt::entity CreateBullet(entt::registry& reg, luna::Shared<luna::TextureAtlas2D> texture, glm::vec2 position, glm::vec2 direction, float speed)
	{
		auto bullet = reg.create();
		reg.emplace<component::Tag>(bullet, "Bullet");
		reg.emplace<component::Renderable>(bullet, texture, 0.075f, 0.075f);
		reg.emplace<component::Transform>(bullet, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
		reg.emplace<component::Velocity>(bullet, glm::vec3(direction.x, direction.y, 0.0f), speed);
		return bullet;
	}

	entt::entity CreateRock(entt::registry& reg, glm::vec2 position, int level, bool turnLeft, float speed)
	{
		auto rock = reg.create();
		reg.emplace<component::Tag>(rock, "Rock");
		reg.emplace<component::Rock>(rock, level, false, turnLeft);
		reg.emplace<component::Collision>(rock);
		reg.emplace<component::Transform>(rock, glm::vec3(position.x, position.y, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
		reg.emplace<component::Velocity>(rock, glm::vec3(randf(-0.5f, 0.5f), randf(-0.5f, 0.5f), 0.0f), speed);

		return rock;
	}

	void SetupLevel(std::mt19937 rng, entt::registry& reg, luna::Shared<luna::TextureAtlas2D> rockTextures[3], unsigned int level)
	{
		int RockSpawn;
		switch (level)
		{
		case 0:
			return;
		case 1:
			RockSpawn = 6;
			break;

		case 2:
			RockSpawn = 12;
			break;

		case 3:
			RockSpawn = 20;
			break;

		default:
			RockSpawn = 100;
			break;
		}

		std::uniform_int_distribution<int> levelGn(1, 3);
		for (int i = 0; i < RockSpawn; i++)
		{
			auto rock = CreateRock(reg, glm::vec2(0.0f, 0.0f), 3, true, 0.1f);
		
			float num = randf(-1.0f, 1.0f);
			auto levelNum = levelGn(rng);
		
			reg.replace<component::Collision>(rock);
			reg.replace<component::Rock>(rock, levelNum, false, num > 0.0f ? true : false);
			float speed = 0.2f;
		
			switch (levelNum)
			{
			case 1:
				reg.emplace<component::Renderable>(rock, rockTextures[2], 0.1f, 0.1f);
				speed = 0.1f;
				break;
			case 2:
				reg.emplace<component::Renderable>(rock, rockTextures[1], 0.125f, 0.125f);
				speed = 0.1f;
				break;
			case 3:
				reg.emplace<component::Renderable>(rock, rockTextures[0], 0.15f, 0.15f);
				speed = 0.001f;
				break;
			}
		
			glm::vec2 rockPos(glm::vec3(randf(-1.0f, 1.0f), randf(-1.0f, 1.0f), 0.0f));
			while (rockPos.x >= -0.5f && rockPos.x <= 0.5f)
				rockPos.x = randf(-1.0f, 1.0f);
		
			while (rockPos.y >= -0.5f && rockPos.y <= 0.5f)
				rockPos.y = randf(-1.0f, 1.0f);
		
			reg.replace<component::Transform>(rock, glm::vec3(rockPos.x, rockPos.y, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
			reg.replace<component::Velocity>(rock, glm::vec3(randf(-0.5f, 0.5f), randf(-0.5f, 0.5f), 0.0f), speed);
		}
	}

	namespace ecs
	{

		using namespace luna;
		Shared<TextureAtlas2D> Ship;
		Shared<TextureAtlas2D> Rocks[3];

		std::random_device rd;
		std::mt19937 rng(rd());

		GameplaySystem::GameplaySystem(std::unordered_map<const char*, luna::Shared<luna::Texture2D>>& textures, int priority) :
			EntitySystem(priority)
		{
			Ship = TextureAtlas2D::CreateFromCoords(textures["ship_rocks"], { 0, 0 }, { 16, 16 });

			Rocks[0] = TextureAtlas2D::CreateFromCoords(textures["ship_rocks"], { 1, 0 }, { 16, 16 });
			Rocks[1] = TextureAtlas2D::CreateFromCoords(textures["ship_rocks"], { 2, 0 }, { 16, 16 });
			Rocks[2] = TextureAtlas2D::CreateFromCoords(textures["ship_rocks"], { 3, 0 }, { 16, 16 });
		}

		GameplaySystem::~GameplaySystem()
		{

		}

		float timer = 0;
		void GameplaySystem::ProcessEntities(entt::registry& reg, luna::Timestep ts)
		{
			auto view = reg.view<component::Gameplay>();
			auto gp  = view.back();
			auto& gameplay = reg.get<component::Gameplay>(gp);

			// General gameplay data and conditions

			if (gameplay.NewGame)
			{
				SetupLevel(rng, reg, Rocks, 1);
				CreatePlayer(reg, Ship);
				gameplay.NewGame = false;
			}

			int rockCount = 0;
			auto rockView = reg.view<component::Rock>();
			for (auto [entity, rock] : rockView.each())
			{
				if (!rock.Broken)
				{
					rockCount++;
					continue;
				}

				reg.destroy(entity);
			}

			auto playerView = reg.view<component::Player>();
			if (playerView.empty()) return;

			// Player related data and conditions

			auto player = playerView.back();
			auto& data = reg.get<component::Player>(player);
			if (data.Alive)
			{
				timer += ts;

				if (timer >= 1.0f)
				{
					LNA_TRACE("Rock Count: {}", rockCount);
					timer = 0;
				}
			}
			else
			{
				if (luna::Input::IsKeyPressed(LNA_KEY_SPACE))
				{
					if (data.Lives <= 0)
					{
						auto allEntities = reg.view<component::Tag>();
						for (auto [entity, data] : allEntities.each())
						{
							if (data.Name.compare("Rock") == 0)
							{
								reg.destroy(entity);
								continue;
							}

							if (data.Name.compare("Player") == 0)
							{
								reg.destroy(entity);
								continue;
							}
						}

						gameplay.NewGame = true;
					}
					else
					{
						reg.emplace_or_replace<component::Transform>(player, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
						reg.emplace_or_replace<component::Velocity>(player, glm::vec3(0.0f), 0.025f);
						data.Alive = true;
					}
				}
			}
		}
	}
}