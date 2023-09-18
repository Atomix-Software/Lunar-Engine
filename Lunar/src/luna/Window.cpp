#include <luna/lnapch.h>
#include "Window.h"

namespace luna {

	Window::Window(const char* title, int width, int height, bool vSync)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;

		initialize(vSync);
	}

	Window::~Window()
	{
		if (m_glfwWindow != nullptr)
			glfwDestroyWindow(m_glfwWindow);

		glfwTerminate();
	}

	void Window::initialize(bool vSync, int syncInterval)
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			throw std::exception();
			return;
		}

		glfwDefaultWindowHints();

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_glfwWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (m_glfwWindow == nullptr)
		{
			std::cout << "Failed to create a Window!" << std::endl;
			glfwTerminate();
			throw std::exception();
			return;
		}

		const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (vid_mode == nullptr)
		{
			throw std::exception();
			return;
		}

		glfwSetWindowPos(m_glfwWindow, (vid_mode->width - m_Data.Width) / 2.0f, (vid_mode->height - m_Data.Height) / 2.0f);

		glfwSwapInterval(vSync ? syncInterval : 0);
		glfwMakeContextCurrent(m_glfwWindow);

		glfwShowWindow(m_glfwWindow);
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}

}