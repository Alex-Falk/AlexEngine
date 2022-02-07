#pragma once

namespace Physics {

	class Node;

	enum class Integrator {
		ZERO,			// No simulation
		SYMPLETIC,		// Simple
		RK2,			// 2nd Order Runge-Kutta
		RK4				// 4th Order Runge-Kutta
	};

	struct CollisionPair
	{
		Node* NodeA;
		Node* NodeB;
	};

	// TODO: this could come from a config file?

	static constexpr float KDTreeMinSize = 2.f;
	static constexpr uint32_t KDTreeMaxNumber = 8;

}