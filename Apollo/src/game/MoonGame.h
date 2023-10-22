#pragma once

#include <Luna.h>
#include <luna/ecs/EntityEngine.h>

namespace game
{
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