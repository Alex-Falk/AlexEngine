#pragma once
#include <string>

#include "Math.h"

class Vector3
{
public:

	Vector3();
	Vector3(const float x, const float y, const float z);
	Vector3(const Vector3& other) = default;
	~Vector3();

	static Vector3 Zero();
	void ToZero();

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	Vector3 Normalized() const;

	float Dist(const Vector3& other) const;
	float DistSqr(const Vector3& other) const;

	std::string ToString() const;

	Vector3 operator-(const Vector3& other) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator*(const float num) const;
	Vector3 operator/(const float num) const;
	Vector3& operator +=(const Vector3& other);
	Vector3& operator -=(const Vector3& other);
	Vector3 operator-() const;

	void Inverse();
	Vector3 Inverted();

	static float Dot(const Vector3& lhs, const Vector3& rhs);
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	void Set(float x, float y, float z);

	float x;
	float y;
	float z;

	static Vector3 Up() { return { 0, 1, 0 }; }
	static Vector3 Right() { return { 1, 0, 0 }; }
	static Vector3 Forward() { return { 0, 0, 1 }; }


	static Vector3 Clamp(const Vector3& vec, const Vector3& min, const Vector3& max)
	{
		return {
			Maths::Clamp(vec.x, min.x, max.x),
			Maths::Clamp(vec.y, min.y, max.y),
			Maths::Clamp(vec.z, min.z, max.z)
		};
	}

};

Vector3 operator*(const float lhs, const Vector3& rhs);