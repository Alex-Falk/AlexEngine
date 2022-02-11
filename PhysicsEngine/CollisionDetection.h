#pragma once
#include <vector>

#include "PhysicsEngine.h"
#include "Maths/Vector3.h"

namespace Physics
{
	class Manifold;
	struct CollisionPair;

	struct CollisionData
	{
		Vector3 CollisionNormal;
		float PenetrationDepth;
		Vector3 OverlapPoint;
	};

	struct Collision
	{
		CollisionPair Pair;
		Manifold* Manifold;
		CollisionData Data;

		std::vector<Vector3> PossibleAxes;
		bool Colliding;
	};

	class CollisionDetection
	{
		static Collision BeginNewPair(CollisionPair pair);
		static bool IsColliding(Collision& collision);
		static void GenContactPoints(Collision& collision);

	protected:
		static bool AddPossibleCollisionAxis(Collision& collision, Vector3 axis);
		static bool CheckCollisionAxis(Collision& collision, const Vector3& axis);
	};

}
