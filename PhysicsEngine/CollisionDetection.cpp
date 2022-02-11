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
	const auto shapeB = pair.NodeA->GetCollisionShape();

	if (!shapeA || !shapeB)
	{
		return false;
	}

	outCollision.NodeA = pair.NodeA;
	outCollision.NodeB = pair.NodeB;

	if (shapeA->GetType() == shapeB->GetType())
	{
		switch(shapeA->GetType())
		{
		case CollisionShape::Sphere:
			{
				const auto sphereA = dynamic_cast<SphereCollisionShape*>(shapeA);
				const auto sphereB = dynamic_cast<SphereCollisionShape*>(shapeB);
				return SphereSphereIntersection(*sphereA, pair.NodeA->GetWorldTransform(), *sphereB, pair.NodeB->GetWorldTransform(), outCollision);
			}
		case CollisionShape::None:
		case CollisionShape::AABB: 
		case CollisionShape::Max:
			NCLERROR("Collision Detection for types other than spheres is not implemented yet")
		}
	}

	return false;
}

bool Physics::CollisionDetection::SphereSphereIntersection(const SphereCollisionShape& sphereA,
	const Matrix4& worldTransformA, const SphereCollisionShape& sphereB, const Matrix4& worldTransformB, Collision& outCollision)
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
