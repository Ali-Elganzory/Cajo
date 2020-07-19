#include "Encircled.h"

Encircled::Encircled(const std::string& name)
	: Layer(name), m_AspectRatio(1280.0f / 720.0f), m_CameraController(m_AspectRatio, true)
{
	m_ExplosionParticles.reserve(m_ParticleNum * 10);

	for (auto& particle : m_Particles)
	{
		bool xAxis = std::rand() % 2;
		float x, y;

		if (xAxis)
		{
			x = std::rand() % 2 ? m_AspectRatio : -m_AspectRatio;
			y = (std::rand() % 1000) / 500.0f - 1.0f;
		}
		else
		{
			y = std::rand() % 2 ? 1.0f : -1.0f;
			x = (std::rand() % 1000) / 500.0f * m_AspectRatio - m_AspectRatio;
		}

		particle = { x, y, 0.0f, 0.0f };
	}
}

void Encircled::OnAttach()
{
	std::srand((uint32_t)time(0));

	m_CircleTexture = Cajo::Texture2D::Create("assets/textures/circle.png");
}

void Encircled::OnDetach()
{
}

void Encircled::OnUpdate(Cajo::Timestep ts)
{
	CAJO_PROFILE_FUNCTION();

	//	OnUpdate
	{
		CAJO_PROFILE_SCOPE("Encircled::Updating");

		m_CameraController.OnUpdate(ts);
		UpdatePlayer(ts);
		UpdateProjectiles(ts);
		UpdateExplosionParticles(ts);
	}

	//	Render
	{
		CAJO_PROFILE_SCOPE("Encircled::Render prep");

		Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cajo::RenderCommand::Clear();
	}

	{
		CAJO_PROFILE_SCOPE("Encircled::Render drawing");

		Cajo::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Cajo::Renderer2D::DrawQuad({ m_PlayerPos.x, m_PlayerPos.y, 0.001f }, m_PlayerScale, m_CircleTexture, m_PlayerColor);

		uint32_t index = 0;
		for (auto& particle : m_Particles)
			Cajo::Renderer2D::DrawQuad({ particle.GetPos().x, particle.GetPos().y, 0.01f * ++index }, { m_ParticleScale, m_ParticleScale }, m_CircleTexture, { 0.4f, 0.2f, 0.6f, 1.0f });
		for (auto& particle : m_ExplosionParticles)
			Cajo::Renderer2D::DrawQuad({ particle.GetPos().x, particle.GetPos().y, 0.01f * ++index }, { m_ExplosionParticleScale, m_ExplosionParticleScale }, m_CircleTexture, particle.GetColor());

		Cajo::Renderer2D::EndScene();
	}
}

void Encircled::OnImGuiRender()
{
}

void Encircled::OnEvent(Cajo::Event& event)
{
	//m_CameraController.OnEvent(event);
}

void Encircled::UpdatePlayer(Cajo::Timestep ts)
{
	if (Cajo::Input::IsKeyPressed(CAJO_KEY_UP))
	{
		m_PlayerPos.y += m_PlayerSpeed * ts;
		if (m_PlayerPos.y > (1.0f - m_PlayerScale.y / 2))
			m_PlayerPos.y = 1.0f - m_PlayerScale.y / 2;
	}
	else if (Cajo::Input::IsKeyPressed(CAJO_KEY_DOWN))
	{
		m_PlayerPos.y -= m_PlayerSpeed * ts;
		if (m_PlayerPos.y < (-1.0f + m_PlayerScale.y / 2))
			m_PlayerPos.y = -1.0f + m_PlayerScale.y / 2;
	}
	if (Cajo::Input::IsKeyPressed(CAJO_KEY_LEFT))
	{
		m_PlayerPos.x -= m_PlayerSpeed * ts;
		if (m_PlayerPos.x < (-m_AspectRatio + m_PlayerScale.x / 2))
			m_PlayerPos.x = -m_AspectRatio + m_PlayerScale.x / 2;
	}
	else if (Cajo::Input::IsKeyPressed(CAJO_KEY_RIGHT))
	{
		m_PlayerPos.x += m_PlayerSpeed * ts;
		if (m_PlayerPos.x > (m_AspectRatio - m_PlayerScale.x / 2))
			m_PlayerPos.x = m_AspectRatio - m_PlayerScale.x / 2;
	}
}

void Encircled::UpdateProjectiles(Cajo::Timestep ts)
{
	for (auto& particle : m_Particles) {
		if (particle.DistTo(0.0f, 0.0f) < 0.1f)
		{
			Explode(particle.GetPos().x, particle.GetPos().y);
			RegenParticle(particle);
		}

		particle.GravitateTo(0.0f, 0.0f, m_Gravity * ts);
		particle.Update(ts);
	}

}

void Encircled::UpdateExplosionParticles(Cajo::Timestep ts)
{
	auto it = m_ExplosionParticles.begin();
	while (it != m_ExplosionParticles.end())
	{
		it->Update(ts);
		if (it->GetPos().y < -(1.0f + m_ExplosionParticleScale))
			it = m_ExplosionParticles.erase(it);
		else
			++it;
	}
}

void Encircled::RegenParticle(Particle& particle)
{
	bool xAxis = std::rand() % 2;
	float x, y;

	if (xAxis)
	{
		x = std::rand() % 2 ? m_AspectRatio : -m_AspectRatio;
		y = (std::rand() % 1000) / 500.0f - 1.0f;
	}
	else
	{
		y = std::rand() % 2 ? 1.0f : -1.0f;
		x = (std::rand() % 1000) / 500.0f * m_AspectRatio - m_AspectRatio;
	}

	particle = { x, y, 0.0f, 0.0f };
}

void Encircled::Explode(float x, float y)
{
	for (int i = 0; i < 10; ++i)
		m_ExplosionParticles.push_back({ x, y, (std::rand() % 1000) / 1000.0f * 0.5f - 0.25f, (std::rand() % 1000) / 1000.0f * 0.5f - 0.25f, -0.5f
			, {(std::rand() % 1000) / 1000.0f * 1.0f, (std::rand() % 1000) / 1000.0f * 1.0f, (std::rand() % 1000) / 1000.0f * 1.0f, 1.0f} });
}