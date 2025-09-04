#pragma once
#include "Framework/Component.h"

class Player : public viper::Component {
public:
	float speed = 500.0f;
	float rotationRate = 180.0f;
	float fireTimer = 0.0f;
	float fireTime = 0.5f;

	Player() = default;
	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
	
	void Read(const viper::json::value_t& value) override;
};
