#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Rocket : public viper::Actor {
public:
	float speed = 350.0f;

	Rocket() = default;
	Rocket(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};