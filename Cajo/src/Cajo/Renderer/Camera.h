#pragma once

#include <glm/glm.hpp>

namespace Cajo {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(const float& left, const float& right, const float& bottom, const float& top);

		void SetProjection(const float& left, const float& right, const float& bottom, const float& top);

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewProjectionMatrix(); }
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(const float& rotation) { m_Rotation = rotation; RecalculateViewProjectionMatrix(); }
		const float& GetRotation() const { return m_Rotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}