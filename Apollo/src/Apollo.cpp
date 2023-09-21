#include <lnapch.h>
#include <Luna.h>

#include <luna/core/EntryPoint.h>

namespace luna
{
	class Sample : public Application
	{
	public:
		Sample(WindowProps& props) :
			Application(props) {}
	};

	Application* CreateApplication()
	{
		WindowProps settings;
		return new Sample(settings);
	}
}