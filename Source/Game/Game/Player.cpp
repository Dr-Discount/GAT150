#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "Math/Math.h"
#include "GameData.h"
#include <SDL3/SDL_scancode.h>
#include "../SpaceGame.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
	float rotate = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) rotate -= 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) rotate += 1;
	
	owner->transform.rotation += (rotate * rotationRate) * dt;
	
	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	vec2 direction{ 1, 0 };
	vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
	//velocity += force * dt;
	auto rb = owner->GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());


	fireTimer -= dt;
	if ((viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer || viper::GetEngine().GetInputSystem().GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) && fireTimer <= 0) {
		fireTimer = fireTime;
		viper::GetEngine().GetAudioSystem().PlaySound("bass");
		owner->fire = true;
	}
}

void Player::OnCollision(viper::Actor* other) {
	if (owner->tag != other->tag) {
		if (other->tag == "enemy") {
			owner->destroyed = true;
			EVENT_NOTIFY(player_dead);
			dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
		}
	}
}

void Player::Read(const viper::json::value_t& value) {
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, rotationRate);
	JSON_GET(value, fireTime);
}
