#include <Luna.h>

namespace Component
{
	struct Renderable
	{
		luna::Shared<luna::TextureAtlas2D> texture;

		float width;
		float height;
	};

	struct Transform
	{
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
	};
}