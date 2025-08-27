#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace viper {
	void Actor::Update(float dt) {
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		for (auto& component : m_components) {
			if (component->active) {
				component->Update(dt);
			}
		}
	}

	void Actor::Draw(Renderer& renderer) {
		if (destroyed) return;

		for (auto& component : m_components) {
			if (component->active) {
				auto result = dynamic_cast<RendererComponent*>(component.get());
				if (result) result->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}