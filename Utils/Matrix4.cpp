#include "Matrix4.h"

#include "Quaternion.h"
#include "Vector4.h"
#include "Vector3.h"

Maths::Matrix4::Matrix4(void) {
	ToIdentity();
}

Maths::Matrix4::Matrix4(float elements[16]) {
	memcpy(this->values, elements, 16 * sizeof(float));
}

Maths::Matrix4::~Matrix4(void) {
	ToIdentity();
}

void Maths::Matrix4::ToIdentity() {
	ToZero();
	values[0] = 1.0f;
	values[5] = 1.0f;
	values[10] = 1.0f;
	values[15] = 1.0f;
}

void Maths::Matrix4::ToZero() {
	for (int i = 0; i < 16; i++) {
		values[i] = 0.0f;
	}
}

Vector3 Maths::Matrix4::GetPositionVector() const {
	return Vector3(values[12], values[13], values[14]);
}

void Maths::Matrix4::SetPositionVector(const Vector3 in) {
	values[12] = in.x;
	values[13] = in.y;
	values[14] = in.z;
}

void Maths::Matrix4::Translate(const Vector3& by)
{
	values[12] += by.x;
	values[13] += by.y;
	values[14] += by.z;
}

void Maths::Matrix4::TranslateLocal(const Vector3& by)
{
	const auto rotated = Quaternion::GetRotation(Vector3::Forward(), GetForwardVector()).Transform(by);
	Translate(rotated);
}

Vector3 Maths::Matrix4::GetScalingVector() const {
	return Vector3(values[0], values[5], values[10]);
}

void Maths::Matrix4::SetScalingVector(const Vector3& in) {
	values[0] = in.x;
	values[5] = in.y;
	values[10] = in.z;
}

Vector3 Maths::Matrix4::GetForwardVector() const
{
	return { values[8], values[9], values[10] };
}

Maths::Matrix4 Maths::Matrix4::CreatePerspectiveMatrix(float znear, float zfar, float aspect, float fov) {
	Matrix4 m;

	const float h = 1.0f / tan(fov * PI_OVER_360);
	float neg_depth = znear - zfar;

	m.values[0] = h / aspect;
	m.values[5] = h;
	m.values[10] = (zfar + znear) / neg_depth;
	m.values[11] = -1.0f;
	m.values[14] = 2.0f * (znear * zfar) / neg_depth;
	m.values[15] = 0.0f;

	return m;
}

//http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
Maths::Matrix4 Maths::Matrix4::CreateOrthographicMatrix(float znear, float zfar, float right, float left, float top, float bottom) {
	Matrix4 m;

	m.values[0] = 2.0f / (right - left);
	m.values[5] = 2.0f / (top - bottom);
	m.values[10] = -2.0f / (zfar - znear);

	m.values[12] = -(right + left) / (right - left);
	m.values[13] = -(top + bottom) / (top - bottom);
	m.values[14] = -(zfar + znear) / (zfar - znear);
	m.values[15] = 1.0f;

	return m;
}

Maths::Matrix4 Maths::Matrix4::BuildViewMatrix(const Vector3& from, const Vector3& lookingAt, const Vector3 up = Vector3(0, 1, 0)) {
	Matrix4 r;
	r.SetPositionVector(Vector3(-from.x, -from.y, -from.z));

	Matrix4 m;

	Vector3 f = (lookingAt - from);
	f.Normalize();

	Vector3 s = Vector3::Cross(f, up);
	Vector3 u = Vector3::Cross(s, f);

	s.Normalize();
	u.Normalize();

	m.values[0] = s.x;
	m.values[4] = s.y;
	m.values[8] = s.z;

	m.values[1] = u.x;
	m.values[5] = u.y;
	m.values[9] = u.z;

	m.values[2] = -f.x;
	m.values[6] = -f.y;
	m.values[10] = -f.z;

	return m * r;
}

Maths::Matrix4 Maths::Matrix4::CreateRotationMatrix(float degrees, const Vector3& inaxis) {
	Matrix4 m;

	Vector3 axis = inaxis;

	axis.Normalize();

	float c = cos((float)DegToRad(degrees));
	float s = sin((float)DegToRad(degrees));

	m.values[0] = (axis.x * axis.x) * (1.0f - c) + c;
	m.values[1] = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
	m.values[2] = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);

	m.values[4] = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
	m.values[5] = (axis.y * axis.y) * (1.0f - c) + c;
	m.values[6] = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);

	m.values[8] = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
	m.values[9] = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
	m.values[10] = (axis.z * axis.z) * (1.0f - c) + c;

	return m;
}

Maths::Matrix4 Maths::Matrix4::CreateScaleMatrix(const Vector3& scale) {
	Matrix4 m;

	m.values[0] = scale.x;
	m.values[5] = scale.y;
	m.values[10] = scale.z;

	return m;
}

Maths::Matrix4 Maths::Matrix4::CreateTranslationMatrix(const Vector3& translation) {
	Matrix4 m;

	m.values[12] = translation.x;
	m.values[13] = translation.y;
	m.values[14] = translation.z;

	return m;
}

Maths::Matrix4 Maths::Matrix4::GetTransposedRotation() {
	Matrix4 temp;
	temp.values[0] = values[0];
	temp.values[5] = values[5];
	temp.values[10] = values[10];
	temp.values[1] = values[4];
	temp.values[4] = values[1];
	temp.values[2] = values[8];
	temp.values[8] = values[2];
	temp.values[6] = values[9];
	temp.values[9] = values[6];
	return temp;
}

float Maths::Matrix4::operator[](int index) const
{ return values[index]; }

float& Maths::Matrix4::operator[](int index)
{ return values[index]; }

Maths::Matrix4 Maths::Matrix4::operator*(const Matrix4& a) const
{
	Matrix4 out;
	//Students! You should be able to think up a really easy way of speeding this up...
	for (unsigned int r = 0; r < 4; ++r) {
		for (unsigned int c = 0; c < 4; ++c) {
			out.values[c + (r * 4)] = 0.0f;
			for (unsigned int i = 0; i < 4; ++i) {
				out.values[c + (r * 4)] += this->values[c + (i * 4)] * a.values[(r * 4) + i];
			}
		}
	}
	return out;
}

std::ostream& operator<<(std::ostream& o, const Maths::Matrix4& m)
{
	o << "Mat4(";
	o << "\t" << m.values[0] << "," << m.values[1] << "," << m.values[2] << "," << m.values[3] << std::endl;
	o << "\t\t" << m.values[4] << "," << m.values[5] << "," << m.values[6] << "," << m.values[7] << std::endl;
	o << "\t\t" << m.values[8] << "," << m.values[9] << "," << m.values[10] << "," << m.values[11] << std::endl;
	o << "\t\t" << m.values[12] << "," << m.values[13] << "," << m.values[14] << "," << m.values[15] << " )" << std::endl;
	return o;
}

//Code from taken from GLU library (all rights reserved).
Maths::Matrix4 Maths::Matrix4::GetInverseOf(const Matrix4& rhs) {
	Matrix4 inv;
	float det;
	int i;

	inv[0] = rhs[5] * rhs[10] * rhs[15] -
		rhs[5] * rhs[11] * rhs[14] -
		rhs[9] * rhs[6] * rhs[15] +
		rhs[9] * rhs[7] * rhs[14] +
		rhs[13] * rhs[6] * rhs[11] -
		rhs[13] * rhs[7] * rhs[10];

	inv[4] = -rhs[4] * rhs[10] * rhs[15] +
		rhs[4] * rhs[11] * rhs[14] +
		rhs[8] * rhs[6] * rhs[15] -
		rhs[8] * rhs[7] * rhs[14] -
		rhs[12] * rhs[6] * rhs[11] +
		rhs[12] * rhs[7] * rhs[10];

	inv[8] = rhs[4] * rhs[9] * rhs[15] -
		rhs[4] * rhs[11] * rhs[13] -
		rhs[8] * rhs[5] * rhs[15] +
		rhs[8] * rhs[7] * rhs[13] +
		rhs[12] * rhs[5] * rhs[11] -
		rhs[12] * rhs[7] * rhs[9];

	inv[12] = -rhs[4] * rhs[9] * rhs[14] +
		rhs[4] * rhs[10] * rhs[13] +
		rhs[8] * rhs[5] * rhs[14] -
		rhs[8] * rhs[6] * rhs[13] -
		rhs[12] * rhs[5] * rhs[10] +
		rhs[12] * rhs[6] * rhs[9];

	inv[1] = -rhs[1] * rhs[10] * rhs[15] +
		rhs[1] * rhs[11] * rhs[14] +
		rhs[9] * rhs[2] * rhs[15] -
		rhs[9] * rhs[3] * rhs[14] -
		rhs[13] * rhs[2] * rhs[11] +
		rhs[13] * rhs[3] * rhs[10];

	inv[5] = rhs[0] * rhs[10] * rhs[15] -
		rhs[0] * rhs[11] * rhs[14] -
		rhs[8] * rhs[2] * rhs[15] +
		rhs[8] * rhs[3] * rhs[14] +
		rhs[12] * rhs[2] * rhs[11] -
		rhs[12] * rhs[3] * rhs[10];

	inv[9] = -rhs[0] * rhs[9] * rhs[15] +
		rhs[0] * rhs[11] * rhs[13] +
		rhs[8] * rhs[1] * rhs[15] -
		rhs[8] * rhs[3] * rhs[13] -
		rhs[12] * rhs[1] * rhs[11] +
		rhs[12] * rhs[3] * rhs[9];

	inv[13] = rhs[0] * rhs[9] * rhs[14] -
		rhs[0] * rhs[10] * rhs[13] -
		rhs[8] * rhs[1] * rhs[14] +
		rhs[8] * rhs[2] * rhs[13] +
		rhs[12] * rhs[1] * rhs[10] -
		rhs[12] * rhs[2] * rhs[9];

	inv[2] = rhs[1] * rhs[6] * rhs[15] -
		rhs[1] * rhs[7] * rhs[14] -
		rhs[5] * rhs[2] * rhs[15] +
		rhs[5] * rhs[3] * rhs[14] +
		rhs[13] * rhs[2] * rhs[7] -
		rhs[13] * rhs[3] * rhs[6];

	inv[6] = -rhs[0] * rhs[6] * rhs[15] +
		rhs[0] * rhs[7] * rhs[14] +
		rhs[4] * rhs[2] * rhs[15] -
		rhs[4] * rhs[3] * rhs[14] -
		rhs[12] * rhs[2] * rhs[7] +
		rhs[12] * rhs[3] * rhs[6];

	inv[10] = rhs[0] * rhs[5] * rhs[15] -
		rhs[0] * rhs[7] * rhs[13] -
		rhs[4] * rhs[1] * rhs[15] +
		rhs[4] * rhs[3] * rhs[13] +
		rhs[12] * rhs[1] * rhs[7] -
		rhs[12] * rhs[3] * rhs[5];

	inv[14] = -rhs[0] * rhs[5] * rhs[14] +
		rhs[0] * rhs[6] * rhs[13] +
		rhs[4] * rhs[1] * rhs[14] -
		rhs[4] * rhs[2] * rhs[13] -
		rhs[12] * rhs[1] * rhs[6] +
		rhs[12] * rhs[2] * rhs[5];

	inv[3] = -rhs[1] * rhs[6] * rhs[11] +
		rhs[1] * rhs[7] * rhs[10] +
		rhs[5] * rhs[2] * rhs[11] -
		rhs[5] * rhs[3] * rhs[10] -
		rhs[9] * rhs[2] * rhs[7] +
		rhs[9] * rhs[3] * rhs[6];

	inv[7] = rhs[0] * rhs[6] * rhs[11] -
		rhs[0] * rhs[7] * rhs[10] -
		rhs[4] * rhs[2] * rhs[11] +
		rhs[4] * rhs[3] * rhs[10] +
		rhs[8] * rhs[2] * rhs[7] -
		rhs[8] * rhs[3] * rhs[6];

	inv[11] = -rhs[0] * rhs[5] * rhs[11] +
		rhs[0] * rhs[7] * rhs[9] +
		rhs[4] * rhs[1] * rhs[11] -
		rhs[4] * rhs[3] * rhs[9] -
		rhs[8] * rhs[1] * rhs[7] +
		rhs[8] * rhs[3] * rhs[5];

	inv[15] = rhs[0] * rhs[5] * rhs[10] -
		rhs[0] * rhs[6] * rhs[9] -
		rhs[4] * rhs[1] * rhs[10] +
		rhs[4] * rhs[2] * rhs[9] +
		rhs[8] * rhs[1] * rhs[6] -
		rhs[8] * rhs[2] * rhs[5];

	det = rhs[0] * inv[0] + rhs[1] * inv[4] + rhs[2] * inv[8] + rhs[3] * inv[12];

	if (det == 0) {
		inv.ToIdentity();
		return inv;
	}

	det = 1.f / det;

	for (i = 0; i < 16; i++) {
		inv[i] = inv[i] * det;
	}

	return inv;
}