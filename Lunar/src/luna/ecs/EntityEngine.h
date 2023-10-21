#pragma once

#include "glm/glm.hpp"
#include "EntitySystem.h"

namespace component
{

	struct Tag
	{
		std::string Name = "Entity";
	};

	struct Transform
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);
	};

}

namespace luna
{
	namespace ecs
	{

		class Engine
		{
		public:
			Engine();
			~Engine();

			void OnUpdate(luna::Timestep ts);

			EntitySystem& AddSystem(EntitySystem* system);

			entt::entity CreateEntity(const char* tag);

			inline void Start() { if (!m_Running) m_Running = true; }
			inline void Stop() { if (m_Running) m_Running = false; }

			template<typename Type, typename... Args>
			inline decltype(auto) AddComponent(entt::entity entity, Args &&...args)
			{
				return m_Registry.emplace_or_replace<Type>(entity, std::forward<Args>(args)...);
			}

			inline entt::registry& GetRegistry() { return m_Registry; }

		private:
			std::list<EntitySystem*> m_Systems;
			entt::registry m_Registry;
			bool m_Running;
		};

	}
}