#pragma once

namespace Math
{
	inline float Squared(float val) { return val * val; }

	inline float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }

	inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }

	inline float Clamp(float val, float min, float max) { return Math::Max(Math::Min(val, max), min); }

}
