#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace luna {
	struct WinData {
		std::string Title = "Window";
		unsigned int Width = 600, Height = 400;
	};

	class Window {
	public:
		Window(const char* title, int width, int height, bool vSync = true);
		~Window();

		void update();

		inline bool shouldClose() { return glfwWindowShouldClose(m_glfwWindow); }

	private:
		void initialize(bool vSync = false, int syncInterval = 1);

	private:
		GLFWwindow* m_glfwWindow;
		WinData m_Data;
	};
}