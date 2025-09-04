#include "Scene.h"
#include "../Renderer/Renderer.h"
#include "Actor.h"
#include "../Components/ColliderComponent.h"
#include "../Core/Factory.h"

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

	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start) {
		actor->scene = this;
		if (start) actor->Start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force) {
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if (((*iter)->persistant) || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Read(const json::value_t& value) {
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorvalue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorvalue);

				std::string name = actor->name;
				Factory::Instance().PrototypeRegister<Actor>(name, std::move(actor));
			}
		}

		if (JSON_HAS(value, actors)) {
			for (auto& actorvalue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorvalue);

				AddActor(std::move(actor), false);
			}
		}
	}

	void Scene::Load() {
		for (auto& actor : m_actors) {
			actor->Start();
		}
	}
}