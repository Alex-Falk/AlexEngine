#include "CollisionDetection.h"

#include "CollisionShape.h"
#include "PhysicsEngine.h"
#include "nclgl/NCLDebug.h"

bool Physics::CollisionDetection::ObjectsIntersecting(const CollisionPair& pair, Collision& outCollision)
{
	if (!pair.IsValid())
	{
		NCLERROR("Invalid Collision pair sent to collision detection");
		return false;
	}

	const auto shapeA = pair.NodeA->GetCollisionShape();
	const auto shapeB = pair.NodeB->GetCollisionShape();

	if (!shapeA || !shapeB)
	{
		return false;
	}

	outCollision.NodeA = pair.NodeA;
	outCollision.NodeB = pair.NodeB;

	if (shapeA->GetType() == shapeB->GetType())
	{
		switch (shapeA->GetType())
		{
		case CollisionShape::Sphere:
		{
			const auto sphereA = dynamic_cast<SphereCollisionShape*>(shapeA);
			const auto sphereB = dynamic_cast<SphereCollisionShape*>(shapeB);
			return SphereSphereIntersection(*sphereA, pair.NodeA->GetWorldTransform(), *sphereB, pair.NodeB->GetWorldTransform(), outCollision);
		}
		case CollisionShape::AABB:
		{
				const auto aabbA = dynamic_cast<AABBCollisionShape*>(shapeA);
				const auto aabbB = dynamic_cast<AABBCollisionShape*>(shapeB);
				return AABBAABBIntersection(*aabbA, pair.NodeA->GetWorldTransform(), *aabbB, pair.NodeB->GetWorldTransform(), outCollision);
		}
		default:
			NCLERROR("Collision Detection for types other than spheres is not implemented yet")
		}
	}
	else if (shapeA->GetType() == CollisionShape::AABB && shapeB->GetType() == CollisionShape::Sphere)
	{
		const auto aabb = dynamic_cast<AABBCollisionShape*>(shapeA);
		const auto sphere = dynamic_cast<SphereCollisionShape*>(shapeB);
		return SphereAABBIntersection(*sphere, pair.NodeB->GetWorldTransform(), *aabb, pair.NodeA->GetWorldTransform(), outCollision);
	}
	else if (shapeA->GetType() == CollisionShape::Sphere && shapeB->GetType() == CollisionShape::AABB)
	{
		const auto aabb = dynamic_cast<AABBCollisionShape*>(shapeB);
		const auto sphere = dynamic_cast<SphereCollisionShape*>(shapeA);
		return SphereAABBIntersection(*sphere, pair.NodeA->GetWorldTransform(), *aabb, pair.NodeB->GetWorldTransform(), outCollision);
	}

	return false;
}

bool Physics::CollisionDetection::SphereSphereIntersection(const SphereCollisionShape& sphereA,
	const Maths::Matrix4& worldTransformA, const SphereCollisionShape& sphereB, const Maths::Matrix4& worldTransformB, Collision& outCollision)
{
	float radiiSum = sphereA.GetRadius() + sphereB.GetRadius();
	Vector3 delta = worldTransformB.GetPositionVector() - worldTransformA.GetPositionVector();
	float dist = delta.Length();

	if (dist < radiiSum)
	{
		const float penetration = (radiiSum - dist);
		const Vector3 normal = delta.Normalized();
		const Vector3 posRelToA = normal * sphereA.GetRadius();
		const Vector3 posRelToB = -normal * sphereB.GetRadius();

		outCollision.SetContactPoint(posRelToA, posRelToB, normal, penetration);
		return true;
	}

	return false;
}

bool Physics::CollisionDetection::AABBAABBIntersection(const AABBCollisionShape& aabbA, const Maths::Matrix4& worldTransformA,
	const AABBCollisionShape& aabbB, const Maths::Matrix4& worldTransformB, Collision& outCollision)
{
	if (aabbA.BoundingBox.CollidingWithBoundingBox(aabbB.BoundingBox))
	{
		Vector3 maxA = aabbA.BoundingBox._max + worldTransformA.GetPositionVector();
		Vector3 minA = aabbA.BoundingBox._min + worldTransformA.GetPositionVector();

		Vector3 maxB = aabbB.BoundingBox._max + worldTransformB.GetPositionVector();
		Vector3 minB = aabbB.BoundingBox._min + worldTransformB.GetPositionVector();

		// we need to find which faces overlap
		static const Vector3 faces[6] =
		{
			-Vector3::Right(), Vector3::Right(), -Vector3::Up(), Vector3::Up(), -Vector3::Forward(), Vector3::Forward()
		};

		float distances[6] =
		{
			(maxB.x - minA.x),
			(maxA.x - minB.x),
			(maxB.y - minA.y),
			(maxA.y - minB.y),
			(maxB.z - minA.z),
			(maxA.z - minB.z)
		};

		float penetration = FLT_MAX;
		Vector3 bestAxis;

		for (int i = 0; i < 6; ++i)
		{
			if (distances[i] < penetration)
			{
				penetration = distances[i];
				bestAxis = faces[i];
			}
		}

		outCollision.SetContactPoint(Vector3::Zero(), Vector3::Zero(), bestAxis, penetration);
		return true;
	}

	return false;
}

bool Physics::CollisionDetection::SphereAABBIntersection(const SphereCollisionShape& sphere,
	const Maths::Matrix4& sphereTransform, const AABBCollisionShape& aabb, const Maths::Matrix4& aabbTransform,
	Collision& outCollision)
{
	// Find closet point on the box to the sphere center
	Vector3 delta = aabbTransform.GetPositionVector() - sphereTransform.GetPositionVector();

	Vector3 closest = Vector3::Clamp(delta, -aabb.BoundingBox.GetHalfSize(), aabb.BoundingBox.GetHalfSize());
	
	// If the point is closer than the sphere radius then we have a collision
	Vector3 local = delta - closest;
	float dist = local.Length();

	if (dist < sphere.GetRadius())
	{
		Vector3 normal = local.Normalized();
		float penetration = (sphere.GetRadius() - dist);

		outCollision.SetContactPoint(normal * sphere.GetRadius(), -normal * sphere.GetRadius(), normal, penetration);
		return true;
	}

	return false;
}
