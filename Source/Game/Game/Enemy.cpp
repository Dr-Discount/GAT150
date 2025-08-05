#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector3.h"

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