#pragma once

#include <luna/core/Core.h>
#include <luna/renderer/TextureAtlas2D.h>

namespace component
{
	struct Renderable
	{
		luna::Shared<luna::TextureAtlas2D> texture;

		float width  = 1.0f;
		float height = 1.0f;
	};

	struct Velocity
	{
		glm::vec3 Direction = glm::vec3(0.0f);
		float Speed = 0.5f;
	};

	struct Collision
	{
		bool Collided = false;
		bool Processed = false;
	};

	struct Timer
	{
		float Time = 1.0f;
		float Counter = Time;
	};
}