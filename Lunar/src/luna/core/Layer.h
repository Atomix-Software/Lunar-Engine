#pragma once

#include "luna/core/Core.h"

#include "luna/events/Event.h"
#include "luna/core/Timestep.h"

namespace luna
{
	/*
	* Layer is essentially the instance of the app we'll hand everything over to.
	* A Game Layer for example could be used to handle Game related purposes.
	*/
	class LNA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}