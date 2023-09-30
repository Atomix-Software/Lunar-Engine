#include <lnapch.h>

#include "game/MoonGame.h"
#include <luna/core/EntryPoint.h>

namespace luna
{
	class Sample : public Application
	{
	public:
		Sample(WindowProps& props) :
			Application(props)
		{
			PushLayer(new game::MoonGame());
		}
	};

	Application* CreateApplication()
	{
		WindowProps settings;

		settings.Title = "Astroids";
		settings.Resizable = false;
		settings.Width = 640;
		settings.Height = 640;

		return new Sample(settings);
	}
}