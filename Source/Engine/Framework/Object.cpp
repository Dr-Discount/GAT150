#include "../EnginePCH.h"
#include "Object.h"

void viper::Object::Read(const json::value_t& value) {
	json::Read(value, "name", name);
	json::Read(value, "active", active);
}
