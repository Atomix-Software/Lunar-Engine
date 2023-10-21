#pragma once

#include <entt.hpp>
#include "luna/core/Timestep.h"

namespace luna
{

	namespace ecs
	{
		class EntitySystem
		{
		public:
			EntitySystem(int priority = 0) : m_Priority(priority) {};
			virtual ~EntitySystem() = default;

			virtual void ProcessEntities(entt::registry& reg, luna::Timestep ts) = 0;

			inline int GetPriority() { return m_Priority; }

		protected:
			int m_Priority;
		};

	}
}
