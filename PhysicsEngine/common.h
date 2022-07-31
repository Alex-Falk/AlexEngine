#pragma once
#include <cstdint>

namespace Physics
{
	class PhysicsNode;

	enum class Integrator
	{
		ZERO,
		// No simulation
		SYMPLETIC,
		// Simple
		RK2,
		// 2nd Order Runge-Kutta
		RK4 // 4th Order Runge-Kutta
	};

	// TODO: this could come from a config file?

	static constexpr float OcTreeMinSize = 2.f;
	static constexpr uint32_t OcTreeMaxNumber = 8;
}
