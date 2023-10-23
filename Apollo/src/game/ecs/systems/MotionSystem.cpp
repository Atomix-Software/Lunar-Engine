#include "MotionSystem.h"

#include <luna/ecs/EntityEngine.h>
#include "../Components.hpp"

namespace game
{
	namespace ecs
	{
		MotionSystem::MotionSystem(int priority) :
			EntitySystem(priority)
		{

		}

		MotionSystem::~MotionSystem()
		{

		}

		void MotionSystem::ProcessEntities(entt::registry& reg, luna::Timestep ts)
		{
			auto view = reg.view<component::Tag, component::Renderable, component::Transform, component::Velocity>();

			for (auto [entity, tag, sprite, transform, velocity] : view.each())
			{
				// We Don't want to process Our Stars because they should be static
				if (tag.Name.compare("Star") == 0) continue;

				if (tag.Name.compare("Player") == 0)
				{	// Everything here is related to player movement
					auto& player = entity;
					auto& plyr = reg.get<component::Player>(player);

					if (plyr.TurnLeft)
						transform.Rotation.z -= 180.0f * ts;
					else if (plyr.TurnRight)
						transform.Rotation.z += 180.0f * ts;

					if (transform.Rotation.z >= 360.0f)
						transform.Rotation.z = 0.0f;
					else if (transform.Rotation.z < 0.0f)
						transform.Rotation.z = 360.0f;

					glm::vec2 vel(0.0f);
					if (plyr.Forward)
					{
						vel.x = velocity.Speed * -glm::cos(glm::radians(transform.Rotation.z));
						vel.y = velocity.Speed * glm::sin(glm::radians(transform.Rotation.z));
					}
					else if (plyr.Backward)
					{
						vel.x = velocity.Speed * glm::cos(glm::radians(transform.Rotation.z));
						vel.y = velocity.Speed * -glm::sin(glm::radians(transform.Rotation.z));
					}

					velocity.Direction.x += vel.x;
					velocity.Direction.y += vel.y;

					if (velocity.Direction.x >= 0.5f)
						velocity.Direction.x = 0.5f;
					else if (velocity.Direction.x <= -0.5f)
						velocity.Direction.x = -0.5f;

					if (velocity.Direction.y >= 0.5f)
						velocity.Direction.y = 0.5f;
					else if (velocity.Direction.y <= -0.5f)
						velocity.Direction.y = -0.5f;
				}
				else if (tag.Name.compare("Rock") == 0)
				{
					auto& rock = entity;
					auto& rck = reg.get<component::Rock>(rock);
					if (!rck.RotateLeft)
						transform.Rotation.z += 45.0f * ts;
					else
						transform.Rotation.z -= 45.0 * ts;

					if (transform.Rotation.z >= 360.0f)
						transform.Rotation.z = 0.0f;
					else if (transform.Rotation.z < 0.0f)
						transform.Rotation.z = 360.0f;

				}
				else
				{

				}

				// Looping that should affect all entities

				transform.Position += velocity.Direction * glm::vec3(ts, ts, 0.0f);

				if (transform.Position.x - (transform.Scale.x * sprite.width * 0.5f) >= 1.0f)
					transform.Position.x = -transform.Position.x + transform.Scale.x * sprite.width;
				else if (transform.Position.x + (transform.Scale.x * sprite.height * 0.5f) <= -1.0f)
					transform.Position.x = -transform.Position.x - transform.Scale.x * sprite.width;

				if (transform.Position.y - (transform.Scale.y * sprite.height * 0.5f) >= 1.0f)
					transform.Position.y = -transform.Position.y + transform.Scale.y * sprite.height;
				else if (transform.Position.y + (transform.Scale.y * sprite.height * 0.5f) <= -1.0f)
					transform.Position.y = -transform.Position.y - transform.Scale.y * sprite.height;
			}
		}
	}
}