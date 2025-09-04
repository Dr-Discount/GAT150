#include "CircleCollider2D.h"

namespace viper {
	FACTORY_REGISTER(CircleCollider2D)

	void viper::CircleCollider2D::Update(float dt) {
		//
	}

	bool viper::CircleCollider2D::CheckCollision(ColliderComponent& other) {
		float distance = (owner->transform.position - other.owner->transform.position).Length();
		
		auto collider = dynamic_cast<CircleCollider2D*>(&other);
		if (collider) {
			float radi = radius + collider->radius;
			if (distance <= radi) return true;
		}
		return false;
	}
	void CircleCollider2D::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ(value, radius);
	}
}