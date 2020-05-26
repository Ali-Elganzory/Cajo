#pragma once

#include "Cajo/Core.h"
#include "Cajo/Events/Event.h"

namespace Cajo {

	class CAJO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};

}
