#include "Scene.h"
#include "../Renderer/Renderer.h"
#include "Actor.h"
#include "../Components/ColliderComponent.h"

namespace viper {
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();
				
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	

	void Scene::Draw(class Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}
}