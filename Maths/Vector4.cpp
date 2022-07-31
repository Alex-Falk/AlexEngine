#include "pch.h"
#include "Vector4.h"

Vector4::Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(const Vector3& xyz, const float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
{
}

float Vector4::Length() const
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Vector4 Vector4::operator*(const float num) const
{
	return {x * num, y * num, z * num, w * num};
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4 Vector4::operator-() const
{
	return {-x, -y, -z, -w};
}

Vector4 Vector4::Zero()
{
	return {0.f, 0.f, 0.f, 0.f};
}

float Vector4::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

void Vector4::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Vector4 Vector4::Normalized() const
{
	const float length = Length();
	return {x / length, y / length, z / length, w / length};
}

float Vector4::Dist(const Vector4& other) const
{
	return (*this - other).Length();
}

float Vector4::DistSqr(const Vector4& other) const
{
	return (*this - other).LengthSqr();
}

std::string Vector4::ToString() const
{
	return "Vector4(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}

void Vector4::Set(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

const float Vector4::operator[](const int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return 0;
	}
}

float& Vector4::operator[](const int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return x; // TODO: Cleaner fix for this?
	}
}
