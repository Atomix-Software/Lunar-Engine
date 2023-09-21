#pragma once

#include "luna/core/Core.h"

namespace luna
{
	class LNA_API GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}