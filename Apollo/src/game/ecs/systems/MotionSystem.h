#pragma once

#include <luna/ecs/EntitySystem.h>

namespace game
{
	namespace ecs
	{
		class MotionSystem : public luna::ecs::EntitySystem
		{
		public:
			MotionSystem(int priority = 0);
			virtual ~MotionSystem() override;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) override;
		};
	}
}