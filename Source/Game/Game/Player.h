#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Player : public viper::Actor {
public:
	float speed = 500.0f;
	float rotationRate = 180.0f;
	float fireTimer = 0.0f;
	float fireTime = 0.5f;

public:
	Player() = default;
	Player(viper::Transform transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

};
