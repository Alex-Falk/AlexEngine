#pragma once
#include <string>

#include "Vector3.h"

class Vector4
{
public:
	Vector4() = default;
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector3& xyz, float w);
	Vector4(const Vector4& other) = default;
	~Vector4() = default;

	Vector3 ToVector3() const
	{
		return {x, y, z};
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
	Vector4 operator*(float num) const;
	Vector4& operator +=(const Vector4& other);
	Vector4& operator -=(const Vector4& other);
	Vector4 operator-() const;

	void Set(float x, float y, float z, float w);

	float x;
	float y;
	float z;
	float w;

	const float operator[](int index) const;
	float& operator[](int index);
};

Vector4 operator*(float lhs, const Vector4& rhs);
