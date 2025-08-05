#include "Rocket.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Math/Vector3.h"
#include "GameData.h"
#include "Player.h"

void Rocket::Update(float dt) {
	vec2 force = vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
	velocity = force;

	transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other) {
	if (tag != other->tag && other->tag == "enemy") {
		destroyed = true;
	}
}