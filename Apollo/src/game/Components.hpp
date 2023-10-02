#include <Luna.h>

namespace Component
{
	struct Renderable
	{
		luna::Shared<luna::TextureAtlas2D> texture;

		float width  = 1.0f;
		float height = 1.0f;
	};

	struct Transform
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale    = glm::vec3(1.0f);
	};

	struct Velocity
	{
		glm::vec3 Direction = glm::vec3(0.0f);
		float Speed = 0.5f;
	};
}