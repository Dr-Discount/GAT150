#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

void Enemy::Update(float dt) {
	vec2 force = movementDirection * speed;
	velocity += force * dt;

	transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
	if (tag != other->tag) {
		destroyed = true;
		viper::GetEngine().GetAudioSystem().PlaySound("bass");
		scene->GetGame()->AddPoints(10);
	}
}