#include "pch.h"
#include "Matrix4.h"

#include "Vector4.h"

Maths::Matrix4::Matrix4()
{
    ToIdentity();
}

Maths::Matrix4::Matrix4(float input[4][4])
{
    std::copy(&input[0][0], &input[4][4], m_data);
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

Maths::Matrix4 Maths::Matrix4::operator*(const Matrix4& rhs) const
{
    for(auto i = 0; i < 4; ++i)
    {
        
    }
}

Vector3 Maths::Matrix4::operator*(const Vector3& rhs) const
{
}

Vector4 Maths::Matrix4::operator*(const Vector4& rhs) const
{
}
