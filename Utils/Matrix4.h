#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace Maths
{
	class Matrix4 {
	public:
		Matrix4(void);
		Matrix4(float elements[16]);
		~Matrix4(void);

		float	values[16];

		//Set all matrix values to zero
		void	ToZero();
		//Sets matrix to identity matrix (1.0 down the diagonal)
		void	ToIdentity();

		//Gets the OpenGL position vector (floats 12,13, and 14)
		Vector3 GetPositionVector() const;
		//Sets the OpenGL position vector (floats 12,13, and 14)
		void	SetPositionVector(const Vector3 in);
		void	Translate(const Vector3& by);
		void	TranslateLocal(const Vector3& by);

		//Gets the scale vector (floats 1,5, and 10)
		Vector3 GetScalingVector() const;
		//Sets the scale vector (floats 1,5, and 10)
		void	SetScalingVector(const Vector3& in);

		Vector3 GetForwardVector() const;

		//Creates a rotation matrix that rotates by 'degrees' around the 'axis'
		//Analogous to glRotatef
		static Matrix4 CreateRotationMatrix(float degrees, const Vector3& axis);

		//Creates a scaling matrix (puts the 'scale' vector down the diagonal)
		//Analogous to glScalef
		static Matrix4 CreateScaleMatrix(const Vector3& scale);

		//Creates a translation matrix (identity, with 'translation' vector at
		//floats 12, 13, and 14. Analogous to glTranslatef
		static Matrix4 CreateTranslationMatrix(const Vector3& translation);

		//Creates a perspective matrix, with 'znear' and 'zfar' as the near and 
		//far planes, using 'aspect' and 'fov' as the aspect ratio and vertical
		//field of vision, respectively.
		static Matrix4 CreatePerspectiveMatrix(float znear, float zfar, float aspect, float fov);

		//Creates an orthographic matrix with 'znear' and 'zfar' as the near and 
		//far planes, and so on. Descriptive variable names are a good thing!
		static Matrix4 CreateOrthographicMatrix(float znear, float zfar, float right, float left, float top, float bottom);

		//Builds a view matrix suitable for sending straight to the vertex shader.
		//Puts the camera at 'from', with 'lookingAt' centered on the screen, with
		//'up' as the...up axis (pointing towards the top of the screen)
		static Matrix4 BuildViewMatrix(const Vector3& from, const Vector3& lookingAt, const Vector3 up);

		Matrix4 GetTransposedRotation();
		
		inline float operator[](int index) const;
		inline float& operator[](int index);

		//Added for GameTech - Code from taken from GLU library (all rights reserved).
		static Matrix4 GetInverseOf(const Matrix4& rhs);


		//Multiplies 'this' matrix by matrix 'a'. Performs the multiplication in 'OpenGL' order (ie, backwards)
		inline Matrix4 operator*(const Matrix4& a) const;

		inline Vector3 operator*(const Vector3& v) const
		{
			Vector3 vec;

			vec.x = v.x * values[0] + v.y * values[4] + v.z * values[8] + values[12];
			vec.y = v.x * values[1] + v.y * values[5] + v.z * values[9] + values[13];
			vec.z = v.x * values[2] + v.y * values[6] + v.z * values[10] + values[14];

			const float temp = v.x * values[3] + v.y * values[7] + v.z * values[11] + values[15];

			vec.x = vec.x / temp;
			vec.y = vec.y / temp;
			vec.z = vec.z / temp;

			return vec;
		}

		inline Vector4 operator*(const Vector4& v) const
		{
			return {
				v.x * values[0] + v.y * values[4] + v.z * values[8] + v.w * values[12],
				v.x * values[1] + v.y * values[5] + v.z * values[9] + v.w * values[13],
				v.x * values[2] + v.y * values[6] + v.z * values[10] + v.w * values[14],
				v.x * values[3] + v.y * values[7] + v.z * values[11] + v.w * values[15]
			};
		}
	};
}