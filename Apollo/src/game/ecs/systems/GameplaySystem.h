#pragma once

#include <Luna.h>

#include <random>
#include <luna/ecs/EntitySystem.h>

namespace game
{

	static inline float randf(float min, float max)
	{
		return  min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

	namespace ecs
	{
		class GameplaySystem : public luna::ecs::EntitySystem
		{
		public:
			GameplaySystem(std::unordered_map<const char*, luna::Shared<luna::Texture2D>>& textures, int priority = 0);
			virtual ~GameplaySystem() override;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) override;
			
		};
	}
}