#pragma once
#include "Vector3.h"

class Vector3;
class Vector4;

namespace Maths
{
	class Matrix4
	{
	public:
		Matrix4();
		explicit Matrix4(const float input[4][4]);
		~Matrix4();

		void ToZero();
		void ToIdentity();

		Vector3 GetPositionVector() const;
		void SetPositionVector(const Vector3& pos);
		void TranslatePosition(const Vector3& by);

		Vector3 GetScaleVector() const;
		void SetScaleVector(const Vector3& scale);

		const float* operator[](int index) const;
		float* operator[](int index);

		Matrix4 operator*(const Matrix4& rhs) const;
		Vector3 operator*(const Vector3& rhs) const;
		Vector4 operator*(const Vector4& rhs) const;

		static Matrix4 CreateRotationMatrix(float degrees, const Vector3& axis);
		static Matrix4 CreateScaleMatrix(const Vector3& scale);
		static Matrix4 CreateTranslationMatrix(const Vector3& transform);

		static Matrix4 CreatePerspectiveMatrix(float zNear, float zFar, float aspectRatio, float fov);
		static Matrix4 CreateOrthographicMatrix(float zNear, float zFar, float right, float left, float top,
		                                        float bottom);
		static Matrix4 CreateViewMatrix(const Vector3& from, const Vector3& lookAt, const Vector3& up = Vector3::Up());

		static Matrix4 GetInverseOf(const Matrix4& mtx);

	private:
		float m_data[4][4]{};
	};
}
