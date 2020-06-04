#pragma once

#include "Cajo/Layer.h"

#include "Cajo/Events/ApplicationEvent.h"
#include "Cajo/Events/MouseEvent.h"
#include "Cajo/Events/KeyEvent.h"

namespace Cajo {

	class CAJO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
