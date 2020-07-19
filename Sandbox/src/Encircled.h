#pragma once

#include <Cajo.h>

#include "Particle.h"

class Encircled : public Cajo::Layer
{
public:
	Encircled(const std::string& name);
	virtual ~Encircled() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Cajo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Cajo::Event& event) override;

private:
	void UpdatePlayer(Cajo::Timestep ts);
	void UpdateProjectiles(Cajo::Timestep ts);
	void UpdateExplosionParticles(Cajo::Timestep ts);
	void RegenParticle(Particle& particle);
	void Explode(float x, float y);

private:
	float m_AspectRatio;
	Cajo::OrthographicCameraController m_CameraController;

	Cajo::Ref<Cajo::Texture2D> m_CircleTexture;

	glm::vec3 m_PlayerPos = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_PlayerScale = { 0.3f, 0.3f };
	glm::vec4 m_PlayerColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_PlayerSpeed = 1.0f;

	float m_Gravity = 0.1f;

	static const uint32_t m_ParticleNum = 10;
	std::array<Particle, m_ParticleNum> m_Particles;
	float m_ParticleScale = 0.1f;

	std::vector<Particle> m_ExplosionParticles;
	float m_ExplosionParticleScale = 0.05f;
};