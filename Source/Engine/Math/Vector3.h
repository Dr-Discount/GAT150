#pragma once
#include "Math.h"
#include <cassert>

template<typename T>
struct Vector3 {
	union {
		struct { T x, y, z; };
		struct { T r, g, b; };
	};

	Vector3() = default;
	Vector3(T x, T y, T z) : x{ x }, y{ y }, z { z } {}

	T operator [] (unsigned int index) const { assert(index < 3); return (&x)[index]; }
	T& operator [] (unsigned int index) { assert(index < 3); return (&x)[index]; }

	Vector3 operator + (const Vector3& v) const { return Vector2(x + v.x, y + v.y, z + v.z); }
	Vector3 operator - (const Vector3& v) const { return Vector2(x - v.x, y - v.y, z - v.z); }
	Vector3 operator * (const Vector3& v) const { return Vector2(x * v.x, y * v.y, z * v.z); }
	Vector3 operator / (const Vector3& v) const { return Vector2(x / v.x, y / v.y, z / v.z); }

	Vector3 operator + (float s) const { return Vector2(x + s, y + s, z + s); }
	Vector3 operator - (float s) const { return Vector2(x - s, y - s, z - s); }
	Vector3 operator * (float s) const { return Vector2(x * s, y * s, z * s); }
	Vector3 operator / (float s) const { return Vector2(x / s, y / s, z / s); }
	
	Vector3 operator += (const Vector3& v) { x += v.x; y += v.y, z += v.z; return *this; }
	Vector3 operator -= (const Vector3& v) { x -= v.x; y -= v.y, z -= v.z; return *this; }
	Vector3 operator *= (const Vector3& v) { x *= v.x; y *= v.y, z *= v.z; return *this; }
	Vector3 operator /= (const Vector3& v) { x /= v.x; y /= v.y, z /= v.z; return *this; }

	Vector3 operator += (float s) { x += s; y += s, z += s; return *this; }
	Vector3 operator -= (float s) { x -= s; y -= s, z -= s; return *this; }
	Vector3 operator *= (float s) { x *= s; y *= s, z *= s; return *this; }
	Vector3 operator /= (float s) { x /= s; y /= s, z /= s; return *this; }

	float LenghtSqr() { return x * x + y * y + z * z; }
	float Length() { return viper::math::sqrtf(LenghtSqr()); }
};

template<typename T>
std::ostream& operator << (std::ostream& stream, const Vector3<T>& V) {
	stream << "{" << V.x << ", " << V.y << ", " << V.z << " }";
	return stream;
}

template<typename T>
std::istream& operator >> (std::istream& stream, Vector3<T>& V) {
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
	if (!(stream >> std::ws >> ch) || ch != ',') {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> V.z)) {
		stream.setstate(std::ios::failbit);
		return stream;
	}
	if (!(stream >> std::ws >> ch) || ch != '}') {
		stream.setstate(std::ios::failbit);
		return stream;
	}

	return stream;
}

using ivec3 = Vector3<int>;
using vec3 = Vector3<float>;
