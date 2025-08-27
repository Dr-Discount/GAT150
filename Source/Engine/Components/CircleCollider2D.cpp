#include "CircleCollider2D.h"

namespace viper {
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
}