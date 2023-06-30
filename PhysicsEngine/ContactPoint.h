#pragma once
#include "Utils/Vector3.h"

namespace Physics
{
	struct ContactPoint
	{
		float CollisionNormal;
		float PenetrationDepth;

		Vector3 PosRelativeToA;
		Vector3 PosRelativeToB;

		float TotalContactImpulse;
		Vector3 TotalFrictionImpulse;
	};
}
