#pragma once
#include <string>

namespace viper {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;

		std::string name;
		bool active{ true };
	};
}