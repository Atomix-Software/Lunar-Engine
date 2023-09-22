#pragma once

#include <Luna.h>

namespace luna
{
	class MoonGame : public Layer
	{
	public:
		MoonGame();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;

	private:
		OrthoController m_CamControl;

		Shared<Shader> m_Shader;
		Shared<VertexArray> m_VAO;
		Shared<TextureAtlas2D> m_Texture;
	};
}