#pragma once
#include "Math.h"
#include <cassert>

template<typename T>
struct Vector2 {
	union {
		struct { T x, y; };
		struct { T u, v; };
	};

	Vector2() = default;
	Vector2(T x, T y) : x{ x }, y{ y } {}

	T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
	T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

	Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
	Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

	Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
	Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
	Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
	Vector2 operator / (float s) const { return Vector2(x / s, y / s); }
	
	Vector2 operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2 operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2 operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2 operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

	Vector2 operator += (float s) { x += s; y += s; return *this; }
	Vector2 operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2 operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2 operator /= (float s) { x /= s; y /= s; return *this; }

	float LenghtSqr() { return x * x + y * y; }
	float Length() { return viper::math::sqrtf(LenghtSqr()); }

	Vector2 Normalized() { return *this / Length(); }

	float Angle() const { return viper::math::atan2f(y, x); };

	Vector2 Rotate(float radians) const {
		Vector2 v;
		v.x = x * viper::math::cosf(radians) - y * viper::math::sinf(radians);
		v.y = x * viper::math::sinf(radians) + y * viper::math::cosf(radians);

		return v;
	}
};

template<typename T>
std::ostream& operator << (std::ostream& stream, const Vector2<T>& V) {
	stream << "{ " << V.x << ", " << V.y << " }";
	return stream;
}

template<typename T>
std::istream& operator >> (std::istream& stream, Vector2<T>& V) {
	char ch = '\0';
	if (!(stream >> std::ws >> ch) || ch != '{') {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> V.x)) {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> ch) || ch != ',') {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> V.y)) {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> ch) || ch != '}') {
		stream.setstate(std::ios::failbit);
		return stream;
	}

	return stream;
}

using ivec2 = Vector2<int>;
using vec2 = Vector2<float>;
