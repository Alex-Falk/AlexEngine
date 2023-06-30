#include "pch.h"
#include "Vector2.h"

template <class T>
Vector2<T>::Vector2()
{
}

template <class T>
Vector2<T>::Vector2(const Vector2& other)
{
}

template <class T>
Vector2<T>::~Vector2()
{
}

template<class T>
Vector2<T>::Vector2(const T x, const T y) : x(x), y(y)
{
}

template<class T>
float Vector2<T>::Length() const
{
	return sqrtf((x * x) + (y * y));
}

template<class T>
Vector2<T> Vector2<T>::operator-(const Vector2& other) const
{
	return {x - other.x, y - other.y};
}

template<class T>
Vector2<T> Vector2<T>::operator+(const Vector2& other) const
{
	return {x + other.x, y + other.y};
}

template<class T>
Vector2<T> Vector2<T>::operator*(const float num) const
{
	return {x * num, y * num};
}

template<class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<class T>
Vector2<T> Vector2<T>::operator-() const
{
	return {-x, -y};
}

template<class T>
Vector2<T> Vector2<T>::Zero()
{
	return {0.f, 0.f};
}

template<class T>
void Vector2<T>::ToZero()
{
	x = static_cast<T>(0.f);
	y = static_cast<T>(0.f);
}

template<class T>
float Vector2<T>::LengthSqr() const
{
	return (x * x) + (y * y);
}

template<class T>
void Vector2<T>::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
}

template<class T>
Vector2<T> Vector2<T>::Normalized() const
{
	const float length = Length();
	return {x / length, y / length};
}

template<class T>
float Vector2<T>::Dist(const Vector2& other) const
{
	return (*this - other).Length();
}

template<class T>
float Vector2<T>::DistSqr(const Vector2& other) const
{
	return (*this - other).LengthSqr();
}

template<class T>
std::string Vector2<T>::ToString() const
{
	return "Vector2(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

template<class T>
void Vector2<T>::Set(const T x, const T y)
{
	this->x = x;
	this->y = y;
}
