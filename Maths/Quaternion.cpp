#include "Quaternion.h"

Maths::Quaternion::Quaternion(void)
{
	x = y = z = 0.0f;
	w = 1.0f;
}

Maths::Quaternion::Quaternion(const Vector3& vec, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}

Maths::Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Maths::Quaternion::~Quaternion(void)
{
}

float Maths::Quaternion::Dot(const Quaternion &a, const Quaternion &b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

void Maths::Quaternion::Normalise() {
	float magnitude = sqrt(Dot(*this, *this));

	if (magnitude > 0.0f) {
		float t = 1.0f / magnitude;

		x *= t;
		y *= t;
		z *= t;
		w *= t;
	}
	else
	{
		//Still no rotation, but now a valid quaternion. 
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
}


Maths::Quaternion Maths::Quaternion::operator *(const Quaternion &b) const {
	Quaternion ans;
	ans.w = w * b.w - x * b.x - y * b.y - z * b.z;
	ans.x = w * b.x + x * b.w + y * b.z - z * b.y;
	ans.y = w * b.y + y * b.w + z * b.x - x * b.z;
	ans.z = w * b.z + z * b.w + x * b.y - y * b.x;

	return ans;
}

Maths::Quaternion Maths::Quaternion::operator *(const Vector3 &b) const {
	Quaternion ans;

	ans.w = -(x * b.x) - (y * b.y) - (z * b.z);

	ans.x =  (w * b.x) + (y * b.z) - (z * b.y);
	ans.y =  (w * b.y) + (z * b.x) - (x * b.z);
	ans.z =  (w * b.z) + (x * b.y) - (y * b.x);

	return ans;
}

Vector3 Maths::Quaternion::Transform(const Vector3& point)
{
	//More optimal solution taken from:
	//  https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	return xyz * (2.0f * Vector3::Dot(xyz, point))
		+ point * (w * w - Vector3::Dot(xyz, xyz))
		+ Vector3::Cross(xyz, point) * (2.0f * w);
	
}

Maths::Quaternion Maths::Quaternion::operator*(const float &a) const
{
	return Quaternion(x * a, y * a, z * a, w * a);
}

Maths::Matrix4 Maths::Quaternion::ToMatrix4() const {
	Matrix4 mat;

	float yy = y*y;
	float zz = z*z;
	float xy = x*y;
	float zw = z*w;
	float xz = x*z;
	float yw = y*w;
	float xx = x*x;
	float yz = y*z;
	float xw = x*w;

	mat[0][0] = 1.0f - 2.0f * (yy + zz);
	mat[0][1] = 2.0f * (xy + zw);
	mat[0][2] = 2.0f * (xz - yw);

	mat[1][0] = 2.0f * (xy - zw);
	mat[1][1] = 1.0f - 2.0f * (xx + zz);
	mat[1][2] = 2.0f * (yz + xw);

	mat[2][0] = 2.0f * (xz + yw);
	mat[2][1] = 2.0f * (yz - xw);
	mat[2][2] = 1.0f - 2.0f * (xx + yy);

	return mat;
}

Maths::Matrix3 Maths::Quaternion::ToMatrix3() const {
	Matrix3 mat;

	float yy = y*y;
	float zz = z*z;
	float xy = x*y;
	float zw = z*w;
	float xz = x*z;
	float yw = y*w;
	float xx = x*x;
	float yz = y*z;
	float xw = x*w;

	mat._11 = 1.0f - 2.0f * (yy + zz);
	mat._12 = 2.0f * (xy + zw);
	mat._13 = 2.0f * (xz - yw);

	mat._21 = 2.0f * (xy - zw);
	mat._22 = 1.0f - 2.0f * (xx + zz);
	mat._23 = 2.0f * (yz + xw);

	mat._31 = 2.0f * (xz + yw);
	mat._32 = 2.0f * (yz - xw);
	mat._33 = 1.0f - 2.0f * (xx + yy);

	return mat;
}

Maths::Quaternion Maths::Quaternion::EulerAnglesToQuaternion(float pitch, float yaw, float roll) {
	float y2 = Math::DegToRad(yaw / 2.0f);
	float p2 = Math::DegToRad(pitch / 2.0f);
	float r2 = Math::DegToRad(roll / 2.0f);


	float cosy = cos(y2);
	float cosp = cos(p2);
	float cosr = cos(r2);

	float siny = sin(y2);
	float sinp = sin(p2);
	float sinr = sin(r2);

	Quaternion q;
	q.x = cosr * sinp * cosy + sinr * cosp * siny;
	q.y = cosr * cosp * siny - sinr * sinp * cosy;
	q.z = sinr * cosp * cosy - cosr * sinp * siny;
	q.w = cosr * cosp * cosy + sinr * sinp * siny;

	return q;
};

Maths::Quaternion Maths::Quaternion::AxisAngleToQuaterion(const Vector3& vector, float degrees) {
	const float halfTheta = Math::DegToRad(degrees) * 0.5f;
	const float sinTheta = sin(halfTheta);

	Quaternion q = Quaternion(vector * sinTheta, cos(halfTheta));
	//q.Normalise();
	return q;
}

void Maths::Quaternion::GenerateW() {
	w = 1.0f - (x*x) - (y*y) - (z*z);
	if (w < 0.0f) {
		w = 0.0f;
	}
	else {
		w = -sqrt(w);
	}
}

Maths::Quaternion Maths::Quaternion::Conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

Maths::Quaternion Maths::Quaternion::FromMatrix(const Matrix4 &m) {
	Quaternion q;

	q.w = sqrt(std::max(0.0f, (1.0f + m[0][0] + m[1][1] + m[2][2]))) / 2;
	q.x = sqrt(std::max(0.0f, (1.0f + m[0][0] - m[1][1] - m[2][2]))) / 2;
	q.y = sqrt(std::max(0.0f, (1.0f - m[0][0] + m[1][1] - m[2][2]))) / 2;
	q.z = sqrt(std::max(0.0f, (1.0f - m[0][0] - m[1][1] + m[2][2]))) / 2;

	q.x = (float)_copysign(q.x, m[2][1] - m[1][2]);
	q.y = (float)_copysign(q.y, m[0][2] - m[2][0]);
	q.z = (float)_copysign(q.z, m[1][0] - m[0][1]);

	return q;
}

Maths::Quaternion Maths::Quaternion::Lerp(const Quaternion& start, const Quaternion& end, float factor)
{
	// Interpolate the two quaternions
	//  - This is not recomended over spherical interpolation
	const float factor_a = 1.0f - factor;
	const float factor_b = factor;

	Quaternion out;
	out.x = factor_a * start.x + factor_b * end.x;
	out.y = factor_a * start.y + factor_b * end.y;
	out.z = factor_a * start.z + factor_b * end.z;
	out.w = factor_a * start.w + factor_b * end.w;

	return out;
}

Maths::Quaternion Maths::Quaternion::Slerp(const Quaternion& start, const Quaternion& end, float factor)
{
	//Clamp interpolation between start and end
	factor = std::min(std::max(factor, 0.0f), 1.0f);

	// Calc cos theta (Dot product)
	float cos_theta = Quaternion::Dot(start, end);

	// Quaternions can describe any rotation positively or negatively (e.g -90degrees is the same as 270degrees), however to interpolate
	// correctly we need /both/ quaternions to use the same coordinate system
	Quaternion real_end = end;
	if (cos_theta < 0.0f)
	{
		cos_theta = -cos_theta;
		real_end.x = -end.x;
		real_end.y = -end.y;
		real_end.z = -end.z;
		real_end.w = -end.w;
	}

	//If cosTheta is close to one, just do linear interpolation to avoid divide by zero and floating point issues 
	if (cos_theta > 1.0f - 1e-6f)
	{
		return Lerp(start, end, factor);
	}
	else
	{
		// Calculate interpolation coefficients
		float theta = acosf(cos_theta);			// extract theta from dot product's cos(theta)
		float sin_theta = sinf(theta);		// compute inverse rotation length -> 1.0f / sin(theta)


		float factor_a = sinf((1.0f - factor) * theta) / sin_theta;
		float factor_b = sinf(factor * theta) / sin_theta;


		// Interpolate the two quaternions
		Quaternion out;
		out.x = factor_a * start.x + factor_b * real_end.x;
		out.y = factor_a * start.y + factor_b * real_end.y;
		out.z = factor_a * start.z + factor_b * real_end.z;
		out.w = factor_a * start.w + factor_b * real_end.w;
		out.Normalise();
		return out;
	}
}

Maths::Quaternion Maths::Quaternion::LookAt(const Vector3& from, const Vector3& to, const Vector3& up)
{
	const Vector3 resting_forward_vector = Vector3(0, 0, -1);

	Vector3 forward = (from - to).Normalized();
	//Create look at rotation
	Quaternion out = GetRotation(resting_forward_vector, forward);

	//Correct rotation to use given up vector
	Vector3 up_l = out.Transform(up);
	Vector3 right = Vector3::Cross(forward, up).Normalized();
	Vector3 up_w = Vector3::Cross(right, forward).Normalized();

	Maths::Quaternion fix_spin = GetRotation(up_l, up_w);

	out = fix_spin * out;
	out.Normalise();

	return out;
}

Maths::Quaternion Maths::Quaternion::GetRotation(const Vector3& from_dir, const Vector3& to_dir, const Vector3& up)
{
	float costheta = Vector3::Dot(from_dir, to_dir);

	//Edge cases preventing theta extraction:
	// - Same as default, no rotation
	if (fabs(costheta - 1.0f) < 1e-6f)
	{
		return Maths::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}
	// - Directly opposite default rotation
	else if (fabs(costheta + 1.0f) < 1e-6f)
	{
		return Maths::Quaternion(up, Math::PI::F);
	}

	
	//Otherwise build a new rotation
	float theta = acosf(costheta);
	Vector3 rotAxis = Vector3::Cross(from_dir, to_dir).Normalized();

	return Maths::Quaternion::AxisAngleToQuaterion(rotAxis, Math::RadToDeg(theta));
}