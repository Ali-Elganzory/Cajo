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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};

}
