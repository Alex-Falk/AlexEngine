#pragma once
#include <string>

template <class T>
class Vector2
{
public:
    Vector2();
    Vector2(T x, T y);
    Vector2(const Vector2& other);
    ~Vector2();

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

    void Set(T x, T y);

    T x{};
    T y{};

protected:
private:
};

template <class T>
Vector2<T> operator*(float lhs, const Vector2<T>& rhs);

using Vector2F = Vector2<float>;
