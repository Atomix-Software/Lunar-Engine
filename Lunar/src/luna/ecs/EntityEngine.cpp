#include <lnapch.h>
#include "EntityEngine.h"

namespace luna
{
	namespace ecs
	{

		Engine::Engine() :
			m_Systems(), m_Running(true), m_HighestPriority(0), m_PriorityCounter(0) {}

		Engine::~Engine()
		{
			Stop();

			m_Registry.clear();
			m_Systems.clear();
		}


		void Engine::OnUpdate(luna::Timestep ts)
		{
			if (!m_Running)	return;

			for (EntitySystem* sys : m_Systems)
			{
				if (sys->GetPriority() != m_PriorityCounter) continue;

				sys->ProcessEntities(m_Registry, ts);

				m_PriorityCounter++;
				if (m_PriorityCounter > m_HighestPriority)
					m_PriorityCounter = 0;
			}
		}

		EntitySystem& Engine::AddSystem(EntitySystem* system) 
		{
			if (system->GetPriority() > m_HighestPriority)
				m_HighestPriority = system->GetPriority();

			m_Systems.push_back(system);
			return *m_Systems.back();
		}

		entt::entity Engine::CreateEntity(const char* tag)
		{
			entt::entity entity = m_Registry.create();
			m_Registry.emplace<component::Tag>(entity, tag);
			m_Registry.emplace<component::Transform>(entity);

			return entity;
		}
	}
}