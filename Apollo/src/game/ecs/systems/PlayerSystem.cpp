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
			auto player = view.back();
			auto& plyr = reg.get<component::Player>(player);

			if (plyr.Alive)
			{
				if (static_cast<int>(ts.GetSeconds()) % 2 == 0.0f)
					plyr.Score++;

				plyr.Firing = luna::Input::IsKeyPressed(LNA_KEY_SPACE);

				plyr.Forward = luna::Input::IsKeyPressed(LNA_KEY_W) && !luna::Input::IsKeyPressed(LNA_KEY_S);
				plyr.Backward = !luna::Input::IsKeyPressed(LNA_KEY_W) && luna::Input::IsKeyPressed(LNA_KEY_S);

				plyr.TurnLeft = luna::Input::IsKeyPressed(LNA_KEY_A) && !luna::Input::IsKeyPressed(LNA_KEY_D);
				plyr.TurnRight = !luna::Input::IsKeyPressed(LNA_KEY_A) && luna::Input::IsKeyPressed(LNA_KEY_D);
			}
			else
			{
				if (luna::Input::IsKeyPressed(LNA_KEY_SPACE))
				{
					if (plyr.Lives <= 0)
					{
						plyr.Score = 0;
						plyr.Lives = 3;
					}

					reg.emplace_or_replace<component::Transform>(player, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(1.0f));
					reg.emplace_or_replace<component::Velocity>(player, glm::vec3(0.0f), 0.025f);
					plyr.Alive = true;
				}
			}
		}
	}
}