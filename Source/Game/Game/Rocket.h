#pragma once
#include "Framework/Component.h"

class Rocket : public viper::Component, public viper::Collidable {
public:
	float speed = 350.0f;

	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other) override;
	
	void Read(const viper::json::value_t& value) override;
};
