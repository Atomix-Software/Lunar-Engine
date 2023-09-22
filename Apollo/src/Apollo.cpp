#include <lnapch.h>

#include "MoonGame.h"
#include <luna/core/EntryPoint.h>

namespace luna
{
	class Sample : public Application
	{
	public:
		Sample(WindowProps& props) :
			Application(props) 
		{
			PushLayer(new MoonGame());
		}
	};

	Application* CreateApplication()
	{
		WindowProps settings;
		return new Sample(settings);
	}
}