#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"
#include "Core/Random.h"

class Enemy : public viper::Actor {
public:
	float speed = 100.0f;
	float fireTime = 2.0f;
	float fireTimer = 3.0f;
	vec2 movementDirection{ vec2{ viper::random::getReal(-1.0f, 1.0f), (float)viper::random::getReal(-1.0f, 1.0f) } };
	vec2 rotation{ 0, 0 };

	Enemy() = default;
	Enemy(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};