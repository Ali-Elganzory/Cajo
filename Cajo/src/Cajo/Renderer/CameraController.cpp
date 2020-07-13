#include "cajopch.h"
#include "CameraController.h"

#include "Cajo/Core/Input.h"
#include "Cajo/Core/KeyCodes.h"

namespace Cajo {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep& ts)
	{
		if (Input::IsKeyPressed(CAJO_KEY_A))
			m_CameraPosition.x -= m_ZoomLevel * m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(CAJO_KEY_D))
			m_CameraPosition.x += m_ZoomLevel * m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(CAJO_KEY_S))
			m_CameraPosition.y -= m_ZoomLevel * m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(CAJO_KEY_W))
			m_CameraPosition.y += m_ZoomLevel * m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(CAJO_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			else if (Input::IsKeyPressed(CAJO_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CAJO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CAJO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= 0.25f * e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}