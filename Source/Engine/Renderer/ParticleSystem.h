#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace viper {
	struct Particle {
		bool active{ false };
		vec2 position;
		vec2 velocity;

		vec3 color;
		float lifespan{ 1 };
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle particle);

	private:
		std::vector<Particle> m_particles;

		Particle* GetFreeParticle();
	};
}