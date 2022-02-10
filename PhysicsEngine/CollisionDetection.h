#pragma once
#include "Maths/Vector3.h"

namespace Physics
{
	struct CollisionPair;


	class CollisionDetection
	{
		void BeginNewPair(CollisionPair pair);

	protected:
		bool AddPossibleCollisionAxis(Vector3 axis);
		bool CheckCollisionAxis(const Vector3& axis, )
	};

}
