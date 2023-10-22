#include "PlayerSystem.h"

#include <luna/core/Log.h>
#include <luna/core/Input.h>
#include <luna/core/Keycodes.h>

#include <luna/ecs/EntityEngine.h>

#include "../Components.hpp"

namespace game
{
	namespace ecs
	{
		PlayerSystem::PlayerSystem(int priority) :
			EntitySystem(priority)
		{

		}

		PlayerSystem::~PlayerSystem()
		{

		}

		void PlayerSystem::ProcessEntities(entt::registry& reg, luna::Timestep ts)
		{
			auto view = reg.view<component::Player>();
			entt::entity entity = view.back();
			component::Player player = reg.get<component::Player>(entity);

			player.Firing = luna::Input::IsKeyPressed(LNA_KEY_SPACE);

			auto& trans = reg.get<component::Transform>(entity);
			auto& motion = reg.get<component::Velocity>(entity);
			
			if (luna::Input::IsKeyPressed(LNA_KEY_A))
				trans.Rotation.z -= 180.0f * ts;
			else if (luna::Input::IsKeyPressed(LNA_KEY_D))
				trans.Rotation.z += 180.0f * ts;
			
			if (trans.Rotation.z >= 360.0f)
				trans.Rotation.z = 0.0f;
			else if (trans.Rotation.z < 0.0f)
				trans.Rotation.z = 360.0f;
			
			glm::vec2 velocity(0.0f);
			if (luna::Input::IsKeyPressed(LNA_KEY_W))
			{
				velocity.x = motion.Speed * -glm::cos(glm::radians(trans.Rotation.z));
				velocity.y = motion.Speed * glm::sin(glm::radians(trans.Rotation.z));
			}
			else if (luna::Input::IsKeyPressed(LNA_KEY_S))
			{
				velocity.x = motion.Speed * glm::cos(glm::radians(trans.Rotation.z));
				velocity.y = motion.Speed * -glm::sin(glm::radians(trans.Rotation.z));
			}
			
			motion.Direction.x += velocity.x;
			motion.Direction.y += velocity.y;
			
			if (motion.Direction.x >= 0.5f)
				motion.Direction.x = 0.5f;
			else if (motion.Direction.x <= -0.5f)
				motion.Direction.x = -0.5f;
			
			if (motion.Direction.y >= 0.5f)
				motion.Direction.y = 0.5f;
			else if (motion.Direction.y <= -0.5f)
				motion.Direction.y = -0.5f;
			
			trans.Position += motion.Direction * glm::vec3(ts, ts, 0.0f);
			
			if (trans.Position.x >= 1.0f || trans.Position.x <= -1.0f)
				trans.Position.x = -trans.Position.x;
			
			if (trans.Position.y >= 1.0f || trans.Position.y <= -1.0f)
				trans.Position.y = -trans.Position.y;
		}
	}
}