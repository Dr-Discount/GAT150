#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Rocket : public viper::Actor {
public:
	float speed = 350.0f;

	Rocket() = default;
	Rocket(viper::Transform transform, viper::res_t<viper::Texture> texture)
		: Actor{ transform, texture } {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};