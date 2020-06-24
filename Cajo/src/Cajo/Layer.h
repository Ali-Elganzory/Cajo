#pragma once

#include "Cajo/Core.h"
#include "Cajo/Core/Timestep.h"
#include "Cajo/Events/Event.h"

namespace Cajo {

	class CAJO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};

}
