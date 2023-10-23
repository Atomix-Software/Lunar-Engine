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
			auto entity = view.back();
			auto& player = reg.get<component::Player>(entity);

			player.Firing = luna::Input::IsKeyPressed(LNA_KEY_SPACE);

			player.Forward = luna::Input::IsKeyPressed(LNA_KEY_W) && !luna::Input::IsKeyPressed(LNA_KEY_S);
			player.Backward = !luna::Input::IsKeyPressed(LNA_KEY_W) && luna::Input::IsKeyPressed(LNA_KEY_S);

			player.TurnLeft = luna::Input::IsKeyPressed(LNA_KEY_A) && !luna::Input::IsKeyPressed(LNA_KEY_D);
			player.TurnRight = !luna::Input::IsKeyPressed(LNA_KEY_A) && luna::Input::IsKeyPressed(LNA_KEY_D);
		}
	}
}