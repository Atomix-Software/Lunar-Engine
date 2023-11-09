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
			std::list<entt::entity> rocks, bullets;
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

				if (tag.Name.compare("Bullet") == 0)
				{
					bullets.push_back(entity);
					continue;
				}
			}

			// Comparison
			for (auto rock : rocks)
			{
				auto& plyr = reg.get<component::Player>(player);
				if (!plyr.Alive) return;

				auto& rockComp = reg.get<component::Rock>(rock);
				if (rockComp.Broken)
					continue;

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

				for (entt::entity bullet : bullets)
				{
					auto& bulletTrans = reg.get<component::Transform>(bullet);
					auto& bulletSprite = reg.get<component::Renderable>(bullet);
					auto& bulletCol = reg.get<component::Collision>(bullet);

					glm::vec2 bltPos = glm::vec2(bulletTrans.Position.x, bulletTrans.Position.y);
					glm::vec2 blthalfSize = glm::vec2((bulletTrans.Scale.x * bulletSprite.width) / 2.0f, (bulletTrans.Scale.y * bulletSprite.height) / 2.0f);

					glm::vec2 rkPos = glm::vec2(rockTrans.Position.x, rockTrans.Position.y);
					glm::vec2 rkHalfSize = glm::vec2((rockTrans.Scale.x * rockSprite.width) / 2.0f, (rockTrans.Scale.y * rockSprite.height) / 2.0f);

					// AABB collision check
					bool colX = bltPos.x - blthalfSize.x < rkPos.x + rkHalfSize.x && bltPos.x + blthalfSize.x > rkPos.x - rkHalfSize.x;
					bool colY = bltPos.y - blthalfSize.y < rkPos.y + rkHalfSize.y && bltPos.y + blthalfSize.y > rkPos.y - rkHalfSize.y;

					if (!colX || !colY)
					{
						rockComp.Broken = false;
					}
					else {

						bulletCol.Collided = true;
						rkCol.Collided = true;
						rockComp.Broken = true;
						return;
					}
				}

				if (rockComp.Broken)
					continue;

				// AABB collision check
				bool collisionX = pos.x - halfSize.x < rkPos.x + rkHalfSize.x && pos.x + halfSize.x > rkPos.x - rkHalfSize.x;
				bool collisionY = pos.y - halfSize.y < rkPos.y + rkHalfSize.y && pos.y + halfSize.y > rkPos.y - rkHalfSize.y;

				if (!collisionX || !collisionY)
				{
					col.Collided = false;
					rkCol.Collided = false;
				}
				else
				{
					col.Collided = true;
					rkCol.Collided = true;

					plyr.Alive = false; 
					
					auto gpView = reg.view<component::Gameplay>();
					auto ent = gpView.back();
					auto& gp = reg.get<component::Gameplay>(ent);

					gp.Lives--;

					if (gp.Lives > 0)
					{
						LNA_ERROR("You DIED!");
						LNA_WARN("Current score {}!", gp.Score);
						LNA_WARN("You have {} lives left!", gp.Lives);
						LNA_TRACE("Press SPACE to respawn!");
					}
					else if(gp.Lives <= 0)
					{
						LNA_ERROR("You DIED!");
						LNA_WARN("No more lives left, your final score is {}!", gp.Score);
						LNA_TRACE("Press SPACE to start again!");
					}

					col.Collided = false;
					rkCol.Collided = false;
				}
			}
		}
	}
}