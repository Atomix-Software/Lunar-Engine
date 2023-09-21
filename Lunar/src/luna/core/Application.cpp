#include <lnapch.h>

#include <GLFW/glfw3.h>

#include "Application.h"
#include "luna/core/Input.h"

namespace luna
{
	Application* Application::s_Instance = nullptr;

	Application::Application(WindowProps& props)
	{
		LNA_PROFILE_FUNCTION();

		LNA_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = Unique<Window>(Window::Create(props));
		m_Window->SetEventCallback(LNA_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
	}

	Application::~Application()
	{
		LNA_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		LNA_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		LNA_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		LNA_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LNA_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LNA_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.IsHandled())
				break;

			(*--it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		LNA_PROFILE_FUNCTION();
		while (m_Running)
		{
			{
				LNA_PROFILE_SCOPE("RunLoop");

				float time = (float)glfwGetTime();
				Timestep timestep = time - m_LastFrame;
				m_LastFrame = time;

				if (!m_Minimized)
				{
					{
						LNA_PROFILE_SCOPE("LayerStack OnUpdate");

						for (Layer* layer : m_LayerStack)
							layer->OnUpdate(timestep);
					}
				}

				m_Window->OnUpdate();
			}
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		LNA_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}