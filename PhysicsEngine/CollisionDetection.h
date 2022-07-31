#pragma once
#include <vector>

#include "Maths/Vector3.h"
#include "nclgl/common.h"
#include "Maths/Matrix4.h"


// This is created with help from my University course
// https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/4collisiondetection/Physics%20-%20Collision%20Detection.pdf

namespace Physics
{
	class AABBCollisionShape;
	class PhysicsNode;
	class SphereCollisionShape;
	struct CollisionPair;

	struct ContactPoint
	{
		Vector3 PosRelToA;
		Vector3 PosRelToB;
		Vector3 Normal;
		float Penetration;
	};

	struct Collision
	{
		PhysicsNode* NodeA{};
		PhysicsNode* NodeB{};

		ContactPoint Point;

		void SetContactPoint(const Vector3& posRelToA, const Vector3& posRelToB, const Vector3& normal, float penetration)
		{
			Point.PosRelToA = posRelToA;
			Point.PosRelToB = posRelToB;
			Point.Normal = normal;
			Point.Penetration = penetration;
		}

		 uint16_t FramesLeft{};
	};

	class CollisionDetection
	{
	public:
		static bool ObjectsIntersecting(const CollisionPair& pair, Collision& outCollision);

	private:
		static bool SphereSphereIntersection(const SphereCollisionShape& sphereA, const Maths::Matrix4& worldTransformA , const SphereCollisionShape& sphereB, const Maths::Matrix4& worldTransformB, Collision& outCollision);
		static bool AABBAABBIntersection(const AABBCollisionShape& aabbA, const Maths::Matrix4& worldTransformA, const AABBCollisionShape& sphereB, const Maths::Matrix4& worldTransformB, Collision& outCollision);
		static bool SphereAABBIntersection(const SphereCollisionShape& sphere, const Maths::Matrix4& sphereTransform, const AABBCollisionShape& aabb, const Maths::Matrix4& aabbTransform, Collision& outCollision);
	};

}
