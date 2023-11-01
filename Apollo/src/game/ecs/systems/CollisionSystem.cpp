#include "CollisionSystem.h"

#include <luna/core/Log.h>
#include <luna/ecs/EntityEngine.h>

#include "../Components.hpp"

namespace game
{
	namespace ecs
	{
		CollisionSystem::CollisionSystem(int prioity) :
			EntitySystem(prioity)
		{

		}

		CollisionSystem::~CollisionSystem()
		{

		}

		void CollisionSystem::ProcessEntities(entt::registry& reg, luna::Timestep ts)
		{
			auto player = static_cast<entt::entity>(0);
			std::list<entt::entity> rocks;
			auto view = reg.view<component::Tag, component::Transform, component::Renderable, component::Collision>();

			// Collection
			for (auto [entity, tag, trans, sprite, collision] : view.each())
			{
				if (tag.Name.compare("Player") == 0)
				{
					player = entity;
					continue;
				}

				if (tag.Name.compare("Rock") == 0)
				{
					rocks.push_back(entity);
					continue;
				}
			}

			// Comparison
			for (auto rock : rocks)
			{
				auto& plyr = reg.get<component::Player>(player);
				if (!plyr.Alive) return;

				auto& playerTrans = reg.get<component::Transform>(player);
				auto& playerSprite = reg.get<component::Renderable>(player);
				auto& col = reg.get<component::Collision>(player);

				glm::vec2 pos = glm::vec2(playerTrans.Position.x, playerTrans.Position.y);
				glm::vec2 halfSize = glm::vec2((playerTrans.Scale.x * playerSprite.width) / 2.0f, (playerTrans.Scale.y * playerSprite.height) / 2.0f);

				auto& rockTrans = reg.get<component::Transform>(rock);
				auto& rockSprite = reg.get<component::Renderable>(rock);
				auto& rkCol = reg.get<component::Collision>(rock);

				glm::vec2 rkPos = glm::vec2(rockTrans.Position.x, rockTrans.Position.y);
				glm::vec2 rkHalfSize = glm::vec2((rockTrans.Scale.x * rockSprite.width) / 2.0f, (rockTrans.Scale.y * rockSprite.height) / 2.0f);

				// AABB collision check
				bool collisionX = pos.x - halfSize.x < rkPos.x + rkHalfSize.x && pos.x + halfSize.x > rkPos.x - rkHalfSize.x;
				bool collisionY = pos.y - halfSize.y < rkPos.y + rkHalfSize.y && pos.y + halfSize.y > rkPos.y - rkHalfSize.y;
					
				auto& rockComp = reg.get<component::Rock>(rock);
				if (!collisionX || !collisionY)
				{
					col.Collided = false;
					rkCol.Collided = false;
					rockComp.Broken = false;
				}
				else
				{
					col.Collided = true;
					rkCol.Collided = true;
					rockComp.Broken = true;

					plyr.Alive = false;
					plyr.Lives--;

					if (plyr.Lives > 0)
					{
						LNA_ERROR("You DIED!");
						LNA_WARN("Current score {}!", plyr.Score);
						LNA_WARN("You have {} lives left!", plyr.Lives);

						col.Collided = false;
					}
					else if(plyr.Lives <= 0)
					{
						LNA_ERROR("You DIED!");
						LNA_WARN("No more lives left, your final score is {}!", plyr.Score);

						col.Collided = false;
					}
				}
			}
		}
	}
}