#include "Player.h"
#include "engine.h"
#include "Rocket.h"
#include "Math/Math.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Math/Vector3.h"
#include "GameData.h"
#include <SDL3/SDL_scancode.h>
#include "../SpaceGame.h"

void Player::Update(float dt) {
	viper::Particle particle;
	particle.position = transform.position;
	particle.velocity = vec2{ 2,0 };
	particle.color = vec3{ 255, 255, 255 };
	particle.lifespan = 2.0f;
	viper::GetEngine().GetPS().AddParticle(particle);

	float rotate = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) rotate -= 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) rotate += 1;
	
	transform.rotation += (rotate * rotationRate) * dt;
	
	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	vec2 direction{ 1, 0 };
	vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed;
	velocity += force * dt;

	transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
	if ((viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer || viper::GetEngine().GetInputSystem().GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) && fireTimer <= 0) {
		fireTimer = fireTime;
		viper::GetEngine().GetAudioSystem().PlaySound("bass");

		std::shared_ptr<viper::Model> rocketM = std::make_shared < viper::Model>(GameData::playerPoints, vec3{ 255, 0, 0 });
		viper::Transform transform{ this->transform.position, this->transform.rotation, 2 };
		auto rocket = std::make_unique<Rocket>(transform, rocketM);
		rocket->damping = 0.5f;
		rocket->speed = 1000.0f;
		rocket->lifespan = 0.7f;
		rocket->name = "rocket";
		rocket->tag = "rocket";

		scene->AddActor(std::move(rocket));
	}
	Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
	if (tag != other->tag) {
		if (other->tag == "enemy") {
			destroyed = true;
			dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
			std::cout << "Player destroyed" << std::endl;
		}
	}
}