#include "RenderSystem.h"

#include <Luna.h>
#include "../Components.hpp"

namespace game
{
	namespace ecs
	{
		RenderSystem::RenderSystem(luna::OrthoController& camControl, int priority) :
			EntitySystem(priority), m_CamControl(camControl) 
		{

		}

		RenderSystem::~RenderSystem()
		{

		}

		void RenderSystem::ProcessEntities(entt::registry& reg, luna::Timestep ts)
		{
			luna::RenderCommand::SetClearColor({ .05f, .05f, .05f, 1.f });
			luna::RenderCommand::Clear();

			auto view = reg.view<component::Tag, component::Renderable, component::Transform>();

			luna::Renderer2D::BeginScene(m_CamControl.GetCamera());
			// Rendering every Entity with a Renderable and Transform Component
			for (auto [entity, tag, spr, trans] : view.each())
			{
				if (tag.Name.compare("Player") == 0) continue;
				luna::Renderer2D::DrawRotatedQuad(trans.Position, { spr.width * trans.Scale.x, spr.height * trans.Scale.y }, trans.Rotation.z, spr.texture);
			}
			
			auto pview = reg.view<component::Player, component::Renderable, component::Transform>();
			for (auto [entity, plyer, spr, trans] : pview.each())
			{ 
				if (!plyer.Alive) continue;

				luna::Renderer2D::DrawRotatedQuad(trans.Position, { spr.width * trans.Scale.x, spr.height * trans.Scale.y }, trans.Rotation.z, spr.texture);
			}

			luna::Renderer2D::EndScene();
		}
	}
}