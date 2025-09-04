#pragma once
 
namespace viper {
	class Collidable {
	public:
		virtual ~Collidable() = default;
		virtual void OnCollision(class Actor* other) = 0;
	};
}