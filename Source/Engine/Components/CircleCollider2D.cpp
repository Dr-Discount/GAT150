#include "CircleCollider2D.h"

namespace viper {
	void viper::CircleCollider2D::Update(float dt) {
		//
	}

	bool viper::CircleCollider2D::CheckCollision(ColliderComponent& other) {
		float distance = (owner->transform.position - other.owner->transform.position).Length();
		
		//float distance = (actorA->transform.position - actorB->transform.position).Length();
		//if (distance < actorA->GetRadius() + actorB->GetRadius())


		return false;
	}
}