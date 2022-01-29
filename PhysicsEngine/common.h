#pragma once

namespace Physics {

	enum class Integrator {
		ZERO,			// No simulation
		SYMPLETIC,		// Simple
		RK2,			// 2nd Order Runge-Kutta
		RK4				// 4th Order Runge-Kutta
	};
}