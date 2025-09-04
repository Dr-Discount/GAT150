#pragma once
#include "Object.h"

namespace viper {
	class Component : public Object {
	public:
		Component() = default;
		class Actor* owner{ nullptr };
		
		virtual void Start() {}
		virtual void Destroyed() {}
		virtual void Update(float dt) = 0;
	};
}