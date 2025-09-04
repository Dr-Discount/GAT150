#pragma once
#include "Object.h"
#include "../Math/Transform.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Texture.h"
#include "Component.h"
#include "../Components//RendererComponent.h"
#include <memory>
#include <string>

namespace viper {
	class Actor : public Object {
	public:
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0.0f };
		bool fire{ false };

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };
		bool persistant{ false };

		Transform transform{ {0, 0}, 0, 1 };
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(Transform transform) : 
			transform(transform)
		{}
		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) {}

		Transform& GetTransform() { return transform; }

		void AddComponent(std::unique_ptr<Component> component);
		
		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

		void Read(const json::value_t& value) override;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

	};

	template<typename T>
	inline T* Actor::GetComponent() {
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents() {
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) results.push_back(result);
		}
		return results;
	}
}