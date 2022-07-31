#pragma once
#include <string>

class Vector2
{
public:
	Vector2() = default;
	Vector2(float x, float y);
	Vector2(const Vector2& other) = default;
	~Vector2() = default;

	static Vector2 Zero();
	void ToZero();

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	Vector2 Normalized() const;

	float Dist(const Vector2& other) const;
	float DistSqr(const Vector2& other) const;

	std::string ToString() const;

	Vector2 operator-(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator*(float num) const;
	Vector2& operator +=(const Vector2& other);
	Vector2& operator -=(const Vector2& other);
	Vector2 operator-() const;

	void Set(float x, float y);

	float x{};
	float y{};
protected:
private:
};

Vector2 operator*(float lhs, const Vector2& rhs);
