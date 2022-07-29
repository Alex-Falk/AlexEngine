#pragma once
#include <math.h>

#include <cmath>

namespace Maths
{
	namespace PI
	{
		static constexpr auto F = 3.14159265358979323846f;
		static constexpr auto D = 3.14159265358979323846;
	}

	static constexpr float TWO_PI = 2 * PI::F;
	static constexpr float PI_OVER_360 = PI::F / 360.f;
	
	static auto Squared(const float val) { return val * val; }

	static auto Min(const float lhs, const float rhs) { return lhs < rhs ? lhs : rhs; }

	static auto Max(const float lhs, const float rhs) { return lhs > rhs ? lhs : rhs; }

	static auto Clamp(const float val, const float min, const float max) { return Max(Min(val, max), min); }

	static auto IsFloatZero(const float val) { return std::fabs(val) < std::numeric_limits<float>::epsilon();}
	
	//Radians to degrees
	static auto RadToDeg(const double deg) { return deg * 180.0 / PI::D; }
	static auto RadToDeg(const float deg)	{ return deg * 180.0f / PI::F; }
	
	//Degrees to radians
	static auto DegToRad(const double rad) { return rad * PI::D / 180.0; }
	static auto DegToRad(const float rad) { return rad * PI::F / 180.0f; }
}
