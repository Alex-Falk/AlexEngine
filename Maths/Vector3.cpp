#include "pch.h"
#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z)
{
}

Vector3::~Vector3()
{
}

float Vector3::Length() const
{
	return sqrtf((x * x) + (y * y) + (z + z));
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return { x - other.x, y - other.y, z - other.z };
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return { x + other.x, y + other.y, z + other.z };
}

Vector3 Vector3::operator*(const float num) const
{
	return { x * num, y * num, z * num };
}

Vector3 Vector3::operator/(const float num) const
{
	return { x / num, y / num, z / num };
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return { -x, -y, -z };
}

void Vector3::Inverse()
{
	x = -x;
	y = -y;
	z = -z;
}

Vector3 Vector3::Inverted()
{
	return { -x, -y, -z };
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	return { (lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z),(lhs.x * rhs.y) - (lhs.y * rhs.x) };
}

Vector3 Vector3::Zero()
{
	return { 0.f, 0.f, 0.f};
}

void Vector3::ToZero()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

float Vector3::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3::Normalize()
{
	const float length = Length();

	if (length <= 0.0001f)
		return;

	x /= length;
	y /= length;
	z /= length;
}

Vector3 Vector3::Normalized() const
{
	const float length = Length();

	if (length <= 0.0001f)
		return Vector3::Zero();

	return { x / length, y / length, z / length};
}

float Vector3::Dist(const Vector3& other) const
{
	return (*this - other).Length();
}

float Vector3::DistSqr(const Vector3& other) const
{
	return (*this - other).LengthSqr();
}

std::string Vector3::ToString() const
{
	return "Vector3(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}

void Vector3::Set(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
