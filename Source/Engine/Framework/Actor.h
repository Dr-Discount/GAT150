#pragma once
#include "../Math/Transform.h"
#include "../Renderer/Model.h"
#include <memory>
#include <string>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0.0f };

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };

		Transform transform{ {0, 0}, 0, 1 };
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(Transform transform, class std::shared_ptr<Model> model) : transform(transform), m_model{ model } {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		Transform& GetTransform() { return transform; }
	protected:
		std::shared_ptr<Model> m_model;
	};
}