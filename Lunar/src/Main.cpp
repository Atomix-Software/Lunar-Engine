#include <luna/lnapch.h>

#include "luna/Window.h"

int main(int argc, char* argv[])
{
	luna::Window* win = new luna::Window("Test", 800, 460);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	volatile bool running = true;
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	while (running)
	{
		if (win->shouldClose())
		{
			running = false;
			continue;
		}
		glClear(GL_COLOR_BUFFER_BIT);

		win->update();
	}

	delete win;
	return 0;
}