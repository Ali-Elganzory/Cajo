#pragma once

class Particle
{
public:
	Particle()
		: m_XPos(0.0f), m_YPos(0.0f), m_XVel(0.0f), m_YVel(0.0f), m_Gravity(0.0f), m_Color({ 1.0f, 1.0f, 1.0f, 1.0f })
	{
	}

	Particle(float xPos, float yPos, float xVel, float yVel, float gravity = 0.0f, glm::vec4 color = glm::vec4(1.0f))
		: m_XPos(xPos), m_YPos(yPos), m_XVel(xVel), m_YVel(yVel), m_Gravity(gravity), m_Color(color)
	{
	}

	void Update(Cajo::Timestep ts)
	{
		m_YVel += m_Gravity * ts;
		m_XPos += m_XVel * ts;
		m_YPos += m_YVel * ts;
	}

	void GravitateTo(float x, float y, float gravity)
	{
		float dx = x - m_XPos;
		float dy = y - m_YPos;
		float distance = std::sqrt(dx * dx + dy * dy);
		m_XVel += dx / distance * gravity;
		m_YVel += dy / distance * gravity;
	}

	float DistTo(float x, float y)
	{
		float dx = x - m_XPos;
		float dy = y - m_YPos;
		return std::sqrt(dx * dx + dy * dy);
	}

	glm::vec3 GetPos()
	{
		return { m_XPos, m_YPos, 0.0f };
	}

	glm::vec4& GetColor()
	{
		return m_Color;
	}

private:
	float m_XPos, m_YPos, m_XVel, m_YVel, m_Gravity;
	glm::vec4 m_Color;

};