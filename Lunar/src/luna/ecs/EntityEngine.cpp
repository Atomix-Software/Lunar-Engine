#include <lnapch.h>
#include "EntityEngine.h"

namespace luna
{
	namespace ecs
	{

		Engine::Engine() :
			m_Systems(), m_Running(true) {}

		Engine::~Engine()
		{
			m_Registry.clear();
			m_Systems.clear();
		}


		void Engine::OnUpdate(luna::Timestep ts)
		{
			if (!m_Running)	return;

			for (EntitySystem* sys : m_Systems)
				sys->ProcessEntities(m_Registry, ts);
		}

		EntitySystem& Engine::AddSystem(EntitySystem* system) 
		{
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