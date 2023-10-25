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

	struct Rock
	{
		int Level = 3;
		bool Broken = false, RotateLeft = false;
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

	struct Player
	{
		int Lives = 3, Score = 0;
		bool Alive = true, Firing = false;

		bool Forward = false, Backward = false;
		bool TurnLeft = false, TurnRight = false;
	};
}