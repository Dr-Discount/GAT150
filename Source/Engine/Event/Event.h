#pragma once
#include <string>
#include <variant>
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

namespace viper {
	struct Event {
		using id_t = std::string;
		using data_t = std::variant<int, float, bool, std::string, vec2, vec3>;

		id_t id;
		data_t data;

		Event(const id_t& id, data_t data) : id(id), data(data) {}
	};
}