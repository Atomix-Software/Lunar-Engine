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
			if (view.empty()) return;

			auto player = view.back();
			auto& data = reg.get<component::Player>(player);
			if (!data.Alive) return;

			if (static_cast<int>(ts.GetSeconds()) % 2 == 0.0f)
				data.Score++;

			data.Firing = luna::Input::IsKeyPressed(LNA_KEY_SPACE);

			data.Forward = luna::Input::IsKeyPressed(LNA_KEY_W) && !luna::Input::IsKeyPressed(LNA_KEY_S);
			data.Backward = !luna::Input::IsKeyPressed(LNA_KEY_W) && luna::Input::IsKeyPressed(LNA_KEY_S);

			data.TurnLeft = luna::Input::IsKeyPressed(LNA_KEY_A) && !luna::Input::IsKeyPressed(LNA_KEY_D);
			data.TurnRight = !luna::Input::IsKeyPressed(LNA_KEY_A) && luna::Input::IsKeyPressed(LNA_KEY_D);
		}
	}
}