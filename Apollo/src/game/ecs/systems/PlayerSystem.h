#pragma once

#include <luna/ecs/EntitySystem.h>

namespace game
{
	namespace ecs
	{
		class PlayerSystem : public luna::ecs::EntitySystem
		{
		public:
			PlayerSystem(int priority = 0);
			virtual ~PlayerSystem() override;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) override;
		};
	}
}