#pragma once

#include <luna/ecs/EntityEngine.h>
#include <luna/renderer/OrthoController.h>

namespace game
{
	namespace ecs
	{
		class RenderSystem : public luna::ecs::EntitySystem
		{
		public:
			RenderSystem(luna::OrthoController& camControl, int priority = 0);
			virtual ~RenderSystem() override;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) override;

		private:
			luna::OrthoController& m_CamControl;
		};
	}
}