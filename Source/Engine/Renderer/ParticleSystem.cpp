#include "ParticleSystem.h"
#include "Renderer.h"

namespace viper {
	bool ParticleSystem::Initialize() {
		m_particles.resize(1000);

		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0.0f);
				particle.position += particle.velocity * dt;

			}
		}
	}

	void ParticleSystem::Draw(Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle particle) {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle;
			freeParticle->active = true;
		}
		m_particles.push_back(particle);
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (particle.active = false) {
				return &particle;
			}
		}
		return nullptr;
	}
}