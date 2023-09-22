#pragma once

#include "luna/core/Core.h"
#include "luna/core/Window.h"

#include "luna/core/Timestep.h"
#include "luna/core/LayerStack.h"

#include "luna/events/Event.h"
#include "luna/events/ApplicationEvent.h"

#include "luna/renderer/Renderer.h"

namespace luna
{
	/*
	* The Application class. Handles a Window, a LayerStack, and the Game Loop.
	*/
	class LNA_API Application
	{
	public:
		Application(WindowProps& props);
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrame = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}