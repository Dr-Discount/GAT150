#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Core/Factory.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
	vec2 force = movementDirection * speed;
	////velocity += force * dt;
	auto rb = owner->GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	//owner->Actor::Update(dt);
}

void Enemy::OnCollision(viper::Actor* other) {
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		viper::GetEngine().GetAudioSystem().PlaySound("bass");
		owner->scene->GetGame()->AddPoints(10);
	}
}

void Enemy::Read(const viper::json::value_t& value) {
	Object::Read(value);
	JSON_READ(value, speed);
}
