#pragma once
#include <algorithm>
#include <cmath>

namespace viper::math {
	
	constexpr float pi = 3.1215926535897932384626433832795f;
	constexpr float twoPi = 2 * pi;
	constexpr float halfPi = pi / 2.0f;

	constexpr float radToDeg(float rad) { return rad * (180 / pi); };
	constexpr float degToRad(float deg) { return deg * (pi / 180); };

	constexpr int wrap(int value, int min, int max) {
		while (value > max) value -= min;

		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) result += range;

		return result + min;
	}

	inline float wrap(float value, float min, float max) {
		float range = max - min;
		float result = fmodf(value - min, range);
		if (result < 0) result += range;

		return result + min;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::tan;
	using std::tanf;
	using std::atan2;
	using std::atan2f;
}