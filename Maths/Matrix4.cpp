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

Maths::Matrix4 Maths::Matrix4::operator*(const Matrix4& mtx) const
{
    Matrix4 out;
    for(auto i = 0; i < 4; ++i)
    {
        for(auto j = 0; j < 4; ++j)
        {
            out[i][j] = 0;
            for (auto k = 0; k < 4; ++k)
            {
                out[i][j] += (*this)[i][k] * mtx[k][j];
            }
        }
    }
    return out;
}

Vector3 Maths::Matrix4::operator*(const Vector3& mtx) const
{
    Vector3 out;
    return out;
}

Vector4 Maths::Matrix4::operator*(const Vector4& mtx) const
{
    Vector4 out{};
    for(auto i = 0; i < 4; ++i)
    {
        out[i] = 0;
        for(auto j = 0; j < 4; ++j)
        {
            out[i] += mtx[j] * m_data[j][i];
        }
    }

    return out;
}

Maths::Matrix4 Maths::Matrix4::CreateRotationMatrix(float degrees, const Vector3& axis)
{
    Matrix4 result;
    const Vector3 ax = axis.Normalized();

    const auto cosine = cosf(DegToRad(degrees));
    const auto sine = sinf(DegToRad(degrees));

    result[0][0] = Squared(ax.x) * (1.f - cosine) + cosine;
    result[0][1] = (ax.x * ax.y) * (1.f - cosine) + (ax.z * sine);
    result[0][2] = (ax.z * ax.x) * (1.f - cosine) - (ax.y * sine);

    result[1][0] = (ax.x * ax.y) * (1.f - cosine) - (ax.z * sine);
    result[1][1] = Squared(ax.y) * (1.f - cosine) + cosine;
    result[1][2] = (ax.z * ax.y) * (1.f - cosine) + (ax.x * sine);

    result[2][0] = (ax.x * ax.z) * (1.f - cosine) + (ax.y * sine);
    result[2][1] = (ax.y * ax.z) * (1.f - cosine) - (ax.x * sine);
    result[2][2] = Squared(ax.z) * (1.f - cosine) + cosine;
    
    return result;
}

Maths::Matrix4 Maths::Matrix4::CreateScaleMatrix(const Vector3& scale)
{
    Matrix4 result;
    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;
    return result;
}

Maths::Matrix4 Maths::Matrix4::CreateTranslationMatrix(const Vector3& transform)
{
    Matrix4 result;
    result[2][0] = transform.x;
    result[2][1] = transform.y;
    result[2][2] = transform.z;
    return result;
}

Maths::Matrix4 Maths::Matrix4::CreatePerspectiveMatrix(float zNear, float zFar, float aspectRatio, float fov)
{
    Matrix4 result;

    const float h = 1.0f / tanf(fov*PI_OVER_360);
    const float negDepth = zNear-zFar;

    result[0][0] = h / aspectRatio;
    result[1][1] = h;
    result[2][2] = (zFar + zNear)/negDepth;
    result[2][3] = -1.0f;
    result[3][2] = 2.0f*(zNear*zFar)/negDepth;
    result[3][3] = 0.0f;

    return result;
}

Maths::Matrix4 Maths::Matrix4::CreateOrthographicMatrix(float zNear, float zFar, float right, float left, float top,
    float bottom)
{
	Matrix4 result;

    result[0][0] = 2.f / (right - left);
    result[1][1] = 2.f / (top - bottom);
    result[2][2] = -2.f / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(zFar + zNear) / (zFar - zNear);
    result[3][3] = 1.0f;

	return result;
}

Maths::Matrix4 Maths::Matrix4::CreateViewMatrix(const Vector3& from, const Vector3& lookAt, const Vector3& up)
{
    Matrix4 positionMat;
    positionMat.SetPositionVector(Vector3(-from.x,-from.y,-from.z));

    Matrix4 rotationMat;

    const Vector3 f = (lookAt - from).Normalized();

    Vector3 s = Vector3::Cross(f,up).Normalized();
    Vector3 u = Vector3::Cross(s,f).Normalized();

    rotationMat[0][0] = s.x;
    rotationMat[1][0] = s.y;
    rotationMat[2][0] = s.z;

    rotationMat[0][1] = u.x;
    rotationMat[1][1] = u.y;
    rotationMat[2][1] = u.z;

    rotationMat[0][2] = -f.x;
    rotationMat[1][2] = -f.y;
    rotationMat[2][2] = -f.z;

    return rotationMat*positionMat;
}

Maths::Matrix4 Maths::Matrix4::GetInverseOf(const Matrix4& mtx)
{
Matrix4 inv;

inv[0][0] = mtx[1][1] * mtx[2][2] * mtx[3][3] -
		mtx[1][1] * mtx[2][3] * mtx[3][2] -
		mtx[2][1] * mtx[1][2] * mtx[3][3] +
		mtx[2][1] * mtx[1][3] * mtx[3][2] +
		mtx[3][1] * mtx[1][2] * mtx[2][3] -
		mtx[3][1] * mtx[1][3] * mtx[2][2];

	inv[1][0] = -mtx[1][0] * mtx[2][2] * mtx[3][3] +
		mtx[1][0] * mtx[2][3] * mtx[3][2] +
		mtx[2][0] * mtx[1][2] * mtx[3][3] -
		mtx[2][0] * mtx[1][3] * mtx[3][2] -
		mtx[3][0] * mtx[1][2] * mtx[2][3] +
		mtx[3][0] * mtx[1][3] * mtx[2][2];

	inv[2][0] = mtx[1][0] * mtx[2][1] * mtx[3][3] -
		mtx[1][0] * mtx[2][3] * mtx[3][1] -
		mtx[2][0] * mtx[1][1] * mtx[3][3] +
		mtx[2][0] * mtx[1][3] * mtx[3][1] +
		mtx[3][0] * mtx[1][1] * mtx[2][3] -
		mtx[3][0] * mtx[1][3] * mtx[2][1];

	inv[3][0] = -mtx[1][0] * mtx[2][1] * mtx[3][2] +
		mtx[1][0] * mtx[2][2] * mtx[3][1] +
		mtx[2][0] * mtx[1][1] * mtx[3][2] -
		mtx[2][0] * mtx[1][2] * mtx[3][1] -
		mtx[3][0] * mtx[1][1] * mtx[2][2] +
		mtx[3][0] * mtx[1][2] * mtx[2][1];

	inv[0][1] = -mtx[0][1] * mtx[2][2] * mtx[3][3] +
		mtx[0][1] * mtx[2][3] * mtx[3][2] +
		mtx[2][1] * mtx[0][2] * mtx[3][3] -
		mtx[2][1] * mtx[0][3] * mtx[3][2] -
		mtx[3][1] * mtx[0][2] * mtx[2][3] +
		mtx[3][1] * mtx[0][3] * mtx[2][2];

	inv[1][1] = mtx[0][0] * mtx[2][2] * mtx[3][3] -
		mtx[0][0] * mtx[2][3] * mtx[3][2] -
		mtx[2][0] * mtx[0][2] * mtx[3][3] +
		mtx[2][0] * mtx[0][3] * mtx[3][2] +
		mtx[3][0] * mtx[0][2] * mtx[2][3] -
		mtx[3][0] * mtx[0][3] * mtx[2][2];

	inv[2][1] = -mtx[0][0] * mtx[2][1] * mtx[3][3] +
		mtx[0][0] * mtx[2][3] * mtx[3][1] +
		mtx[2][0] * mtx[0][1] * mtx[3][3] -
		mtx[2][0] * mtx[0][3] * mtx[3][1] -
		mtx[3][0] * mtx[0][1] * mtx[2][3] +
		mtx[3][0] * mtx[0][3] * mtx[2][1];

	inv[3][1] = mtx[0][0] * mtx[2][1] * mtx[3][2] -
		mtx[0][0] * mtx[2][2] * mtx[3][1] -
		mtx[2][0] * mtx[0][1] * mtx[3][2] +
		mtx[2][0] * mtx[0][2] * mtx[3][1] +
		mtx[3][0] * mtx[0][1] * mtx[2][2] -
		mtx[3][0] * mtx[0][2] * mtx[2][1];

	inv[0][2] = mtx[0][1] * mtx[1][2] * mtx[3][3] -
		mtx[0][1] * mtx[1][3] * mtx[3][2] -
		mtx[1][1] * mtx[0][2] * mtx[3][3] +
		mtx[1][1] * mtx[0][3] * mtx[3][2] +
		mtx[3][1] * mtx[0][2] * mtx[1][3] -
		mtx[3][1] * mtx[0][3] * mtx[1][2];

	inv[1][2] = -mtx[0][0] * mtx[1][2] * mtx[3][3] +
		mtx[0][0] * mtx[1][3] * mtx[3][2] +
		mtx[1][0] * mtx[0][2] * mtx[3][3] -
		mtx[1][0] * mtx[0][3] * mtx[3][2] -
		mtx[3][0] * mtx[0][2] * mtx[1][3] +
		mtx[3][0] * mtx[0][3] * mtx[1][2];

	inv[2][2] = mtx[0][0] * mtx[1][1] * mtx[3][3] -
		mtx[0][0] * mtx[1][3] * mtx[3][1] -
		mtx[1][0] * mtx[0][1] * mtx[3][3] +
		mtx[1][0] * mtx[0][3] * mtx[3][1] +
		mtx[3][0] * mtx[0][1] * mtx[1][3] -
		mtx[3][0] * mtx[0][3] * mtx[1][1];

	inv[3][2] = -mtx[0][0] * mtx[1][1] * mtx[3][2] +
		mtx[0][0] * mtx[1][2] * mtx[3][1] +
		mtx[1][0] * mtx[0][1] * mtx[3][2] -
		mtx[1][0] * mtx[0][2] * mtx[3][1] -
		mtx[3][0] * mtx[0][1] * mtx[1][2] +
		mtx[3][0] * mtx[0][2] * mtx[1][1];

	inv[0][3] = -mtx[0][1] * mtx[1][2] * mtx[2][3] +
		mtx[0][1] * mtx[1][3] * mtx[2][2] +
		mtx[1][1] * mtx[0][2] * mtx[2][3] -
		mtx[1][1] * mtx[0][3] * mtx[2][2] -
		mtx[2][1] * mtx[0][2] * mtx[1][3] +
		mtx[2][1] * mtx[0][3] * mtx[1][2];

	inv[1][3] = mtx[0][0] * mtx[1][2] * mtx[2][3] -
		mtx[0][0] * mtx[1][3] * mtx[2][2] -
		mtx[1][0] * mtx[0][2] * mtx[2][3] +
		mtx[1][0] * mtx[0][3] * mtx[2][2] +
		mtx[2][0] * mtx[0][2] * mtx[1][3] -
		mtx[2][0] * mtx[0][3] * mtx[1][2];

	inv[2][3] = -mtx[0][0] * mtx[1][1] * mtx[2][3] +
		mtx[0][0] * mtx[1][3] * mtx[2][1] +
		mtx[1][0] * mtx[0][1] * mtx[2][3] -
		mtx[1][0] * mtx[0][3] * mtx[2][1] -
		mtx[2][0] * mtx[0][1] * mtx[1][3] +
		mtx[2][0] * mtx[0][3] * mtx[1][1];

	inv[3][3] = mtx[0][0] * mtx[1][1] * mtx[2][2] -
		mtx[0][0] * mtx[1][2] * mtx[2][1] -
		mtx[1][0] * mtx[0][1] * mtx[2][2] +
		mtx[1][0] * mtx[0][2] * mtx[2][1] +
		mtx[2][0] * mtx[0][1] * mtx[1][2] -
		mtx[2][0] * mtx[0][2] * mtx[1][1];

	float det = mtx[0][0] * inv[0][0] + mtx[0][1] * inv[1][0] + mtx[0][2] * inv[2][0] + mtx[0][3] * inv[3][0];

	if (IsFloatZero(det)) {
		inv.ToIdentity();
		return inv;
	}

	det = 1.f / det;

	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; ++j)
		{
			inv[i][j] = inv[i][j] * det;
		}
	}

	return inv;
}
