#include "../GamePCH.h"
#include "Rocket.h"
#include "GameData.h"
#include "Player.h"
#include "Core/Factory.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
	vec2 force = vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
	auto rb = owner->GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());
}

void Rocket::OnCollision(viper::Actor* other) {
	if (owner->tag != other->tag && other->tag == "enemy") {
		owner->destroyed = true;
	}
}

void Rocket::Read(const viper::json::value_t& value) {
	Object::Read(value);
	JSON_READ(value, speed);
}
