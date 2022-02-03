#pragma once
#include <string>

#include "Vector3.h"

class Vector4
{
public:

	Vector4() = default;
	Vector4(const float x, const float y, const float z, const float w);
	Vector4(const Vector4& other) = default;
	~Vector4() = default;

	Vector3 ToVector3() const {
		return  { x, y, z };
	}


	static Vector4 Zero();

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	Vector4 Normalized() const;

	float Dist(const Vector4& other) const;
	float DistSqr(const Vector4& other) const;

	std::string ToString() const;

	Vector4 operator-(const Vector4& other) const;
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator*(const float num) const;
	Vector4& operator +=(const Vector4& other);
	Vector4& operator -=(const Vector4& other);
	Vector4 operator-() const;

	void Set(float x, float y, float z, float w);

	float x;
	float y;
	float z;
	float w;

};

Vector4 operator*(const float lhs, const Vector4& rhs);