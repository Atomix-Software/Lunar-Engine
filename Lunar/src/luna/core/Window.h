#pragma once

#include <lnapch.h>

#include "luna/core/Core.h"
#include "luna/events/Event.h"

namespace luna
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool Resizable;

		WindowProps(const std::string& title = "Lunar Engine", unsigned int width = 1280, unsigned height = 720, bool resizable = true)
			: Title(title), Width(width), Height(height), Resizable(resizable) { }
	};

	// Interface for a Desktop System based Window
	class LNA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetResizable(bool enabled) = 0;
		virtual bool IsResizable() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Unique<Window> Create(const WindowProps& props = WindowProps());
	};
}