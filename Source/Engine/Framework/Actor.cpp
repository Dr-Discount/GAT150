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

	float Actor::GetRadius() {
		//return (m_texture) ? (m_texture->GetSize().Length() * 0.5f) * transform.scale * 0.9f : 0;
		return 50.0f;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}