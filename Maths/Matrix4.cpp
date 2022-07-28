#include "pch.h"
#include "Matrix4.h"

#include "Vector4.h"

Maths::Matrix4::Matrix4()
{
    ToIdentity();
}

Maths::Matrix4::Matrix4(const float input[4][4])
{
    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            m_data[i][j] = input[i][j];
        }
    }
}


Maths::Matrix4::~Matrix4()
{
}

void Maths::Matrix4::ToZero()
{
    for(auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            m_data[i][j] = 0;
        }
    }
}

void Maths::Matrix4::ToIdentity()
{
    ToZero();
    for(auto i = 0; i < 4; ++i)
    {
        m_data[i][i] = 1.f;
    }
}

Vector3 Maths::Matrix4::GetPositionVector() const
{
    return { m_data[3][0], m_data[3][1], m_data[3][2] };
}

void Maths::Matrix4::SetPositionVector(const Vector3& pos)
{
    m_data[3][0] = pos.x;
    m_data[3][1] = pos.y;
    m_data[3][2] = pos.z;
}

void Maths::Matrix4::TranslatePosition(const Vector3& by)
{
    m_data[3][0] += by.x;
    m_data[3][1] += by.y;
    m_data[3][2] += by.z;
}

Vector3 Maths::Matrix4::GetScaleVector() const
{
    return { m_data[0][0], m_data[1][1], m_data[2][2] };
}

void Maths::Matrix4::SetScaleVector(const Vector3& scale)
{
    m_data[0][0] = scale.x;
    m_data[1][1] = scale.y;
    m_data[2][2] = scale.z;
}

float const* Maths::Matrix4::operator[](const int index) const
{
    return m_data[index];
}

float* Maths::Matrix4::operator[](const int index)
{
    return m_data[index];
}

Maths::Matrix4 Maths::Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 out;
    for(auto i = 0; i < 4; ++i)
    {
        for(auto j = 0; j < 4; ++j)
        {
            out[i][j] = 0;
            for (auto k = 0; k < 4; ++k)
            {
                out[i][j] += (*this)[i][k] * rhs[k][j];
            }
        }
    }
    return out;
}

Vector3 Maths::Matrix4::operator*(const Vector3& rhs) const
{
    Vector3 out;
    return out;
}

Vector4 Maths::Matrix4::operator*(const Vector4& rhs) const
{
    Vector4 out{};
    for(auto i = 0; i < 4; ++i)
    {
        out[i] = 0;
        for(auto j = 0; j < 4; ++j)
        {
            out[i] += rhs[j] * m_data[j][i];
        }
    }

    return out;
}

Maths::Matrix4 Maths::Matrix4::CreateRotationMatrix(float degrees, const Vector3& axis)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::CreateScaleMatrix(const Vector3& scale)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::CreateTranslationMatrix(const Vector3& transform)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::CreatePerspectiveMatrix(float zNear, float zFar, float aspectRatio, float fov)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::CreateOrthographicMatrix(float zNear, float zFar, float right, float left, float top,
    float bottom)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::CreateViewMatrix(const Vector3& from, const Vector3& lookAt, const Vector3& up)
{
    return {};
}

Maths::Matrix4 Maths::Matrix4::GetInverseOf(const Matrix4& mtx)
{
    return {};
}
