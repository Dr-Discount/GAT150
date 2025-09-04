#pragma once

namespace viper {

	template<typename T>
	struct Rect {
		Rect() = default;
		Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

		T x = 0;
		T y = 0;
		T w = 0;
		T h = 0;
	};

	using rect = Rect<float>;
	using irect = Rect<int>;
}