#pragma once

#include <Luna.h>
#include <luna/ecs/EntityEngine.h>

namespace game
{
	//class Ship
	//{
	//public:
	//	Ship(luna::Shared<luna::TextureAtlas2D> texture, entt::registry& registry, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3 scale = glm::vec3(1.0f));
	//
	//	void OnUpdate(luna::Timestep ts);
	//	void OnRender(luna::Timestep ts);
	//
	//	inline entt::entity GetId() { return m_Id; }
	//
	//private:
	//	entt::entity m_Id;
	//};

	class MoonGame : public luna::Layer
	{
	public:
		MoonGame();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(luna::Timestep ts) override;
		virtual void OnEvent(luna::Event& event) override;

	private:
		luna::OrthoController m_CamControl;
		luna::ecs::Engine m_Engine;

		luna::Shared<luna::Shader> m_Shader;
		luna::Shared<luna::VertexArray> m_VAO;
		std::unordered_map<const char*, luna::Shared<luna::Texture2D>> m_Textures;
	};
}