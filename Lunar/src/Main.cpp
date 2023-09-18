#include <luna/lnapch.h>

#include "luna/Window.h"

int main(int argc, char* argv[])
{
	luna::Window* win = new luna::Window("Test", 800, 600);
	volatile bool running = true;

	while (running)
	{
		if (win->shouldClose())
		{
			running = false;
			continue;
		}

		win->update();
	}

	delete win;
	return 0;
}