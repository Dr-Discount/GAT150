#pragma once
#include "Framework/Component.h"

class Rocket : public viper::Component {
public:
	float speed = 350.0f;

	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);
	
	void Read(const viper::json::value_t& value) override;
};
