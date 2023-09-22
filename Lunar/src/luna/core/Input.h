#pragma once

#include "luna/core/Core.h"

namespace luna
{
	/*
	* Simple static class for Input.
	* Lets us get keyboard and mouse input.
	*/
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);

		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}