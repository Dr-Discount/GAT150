#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/Factory.h"

namespace viper {
	FACTORY_REGISTER(Actor)

	Actor::Actor(const Actor& other) : Object{ other } ,
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform } {
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

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

	void Actor::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistant);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		if (JSON_HAS(value, components)) {
			for (auto& componentvalue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentvalue, type);
				
				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentvalue);

				AddComponent(std::move(component));
			}
		}
	}
}