#pragma once
#include "Framework/Component.h"
#include "Core/Random.h"

class Enemy : public viper::Component, public viper::Collidable {
public:
	float speed = 100.0f;
	float fireTime = 2.0f;
	float fireTimer = 3.0f;
	vec2 movementDirection{ vec2{ viper::random::getReal(-1.0f, 1.0f), (float)viper::random::getReal(-1.0f, 1.0f) } };
	vec2 rotation{ 0, 0 };

	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other) override;
	void Read(const viper::json::value_t& value) override;
};