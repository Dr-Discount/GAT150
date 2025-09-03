#pragma once
#include "Framework/Actor.h"


class Rocket : public viper::Actor {
public:
	float speed = 350.0f;

	Rocket() = default;
	Rocket(viper::Transform transform)
		: Actor{ transform} {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};