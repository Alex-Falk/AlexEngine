#pragma once
#include <math.h>

namespace Math
{
	namespace PI
	{
		static constexpr auto F = 3.14159265358979323846f;
		static constexpr auto D = 3.14159265358979323846;
	}

	static constexpr float TWO_PI = 2 * PI::F;
	static constexpr float PI_OVER_360 = PI::F / 360.f;
	
	static auto Squared(float val) { return val * val; }

	static auto Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }

	static auto Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }

	static auto Clamp(float val, float min, float max) { return Max(Min(val, max), min); }
	
	//Radians to degrees
	static auto RadToDeg(const double deg) { return deg * 180.0 / PI::D; }
	static auto RadToDeg(const float deg)	{ return deg * 180.0f / PI::F; }
	
	//Degrees to radians
	static auto DegToRad(const double rad) { return rad * PI::D / 180.0; }
	static auto DegToRad(const float rad) { return rad * PI::F / 180.0f; }
}
