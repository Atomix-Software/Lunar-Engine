#pragma once

#include <luna/ecs/EntitySystem.h>

namespace game
{
	namespace ecs
	{
		class CollisionSystem : public luna::ecs::EntitySystem
		{
		public:
			CollisionSystem(int prioity = 0);
			virtual ~CollisionSystem() override;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) override;
		};
	}
}