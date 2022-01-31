#include "pch.h"
#include "Vector2.h"


Vector2::Vector2(const float x, const float y) : x(x), y(y)
{
}

float Vector2::Length() const
{
	return sqrtf((x * x) + (y * y));
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return { x - other.x, y - other.y };
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return { x + other.x, y + other.y };
}

Vector2 Vector2::operator*(const float num) const
{
	return { x * num, y * num };
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

Vector2 Vector2::Zero()
{
	return {0.f, 0.f};
}

void Vector2::ToZero()
{
	x = 0.f;
	y = 0.f;
}

float Vector2::LengthSqr() const
{
	return (x * x) + (y * y);
}

void Vector2::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
}

Vector2 Vector2::Normalized() const
{
	const float length = Length();
	return {x / length, y / length};
}

float Vector2::Dist(const Vector2& other) const
{
	return (*this - other).Length();
}

float Vector2::DistSqr(const Vector2& other) const
{
	return (*this - other).LengthSqr();
}

std::string Vector2::ToString() const
{
	return "Vector2(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

void Vector2::Set(const float x, const float y)
{
	this->x = x;
	this->y = y;
}
