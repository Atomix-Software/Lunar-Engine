#pragma once

#include <GLFW/glfw3.h>

#include "luna/core/Log.h"
#include "luna/core/Window.h"
#include "luna/renderer/GraphicsContext.h"

struct GLFWwindow;
namespace luna
{
	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();

		void OnUpdate() override;

		virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; }

		virtual inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void SetResizable(bool enabled) override;
		virtual bool IsResizable() const override;

		virtual inline void* GetNativeWindow() const { return (void*)m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		Unique<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned Width, Height;
			bool VSync;
			bool Resizable;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}