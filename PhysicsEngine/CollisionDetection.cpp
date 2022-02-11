#include "CollisionDetection.h"
#include "CollisionDetection.h"

#include <list>

#include "CollisionShape.h"
#include "Manifold.h"
#include "nclgl/Plane.h"

Physics::Collision Physics::CollisionDetection::BeginNewPair(CollisionPair pair)
{
	return {};
}

bool Physics::CollisionDetection::IsColliding(Collision& collision)
{
	if (!collision.Pair.NodeA || !collision.Pair.NodeB)
	{
		return false;
	}

	std::vector<Vector3> axes1, axes2;

	collision.Pair.NodeA->GetCollisionShape()->GetCollisionAxes(collision.Pair.NodeB, axes1);
	for (const Vector3& axis : axes1)
		AddPossibleCollisionAxis(collision, axis);

	collision.Pair.NodeB->GetCollisionShape()->GetCollisionAxes(collision.Pair.NodeA, axes2);
	for (const Vector3& axis : axes2)
		AddPossibleCollisionAxis(collision, axis);

	for (const Vector3& norm1 : axes1) {
		for (const Vector3& norm2 : axes2) {
			AddPossibleCollisionAxis(collision, Vector3::Cross(norm1, norm2).Normalized());
		}
	}

	CollisionData currentData;
	currentData.PenetrationDepth = -FLT_MAX;

	collision.Data.PenetrationDepth = -FLT_MAX;
	for (const Vector3& axis : collision.PossibleAxes) {
		// If the collision axis does NOT intersect then return
		// immediately as we know that atleast in one direction / axis
		// the two objects do not intersect

		if (!CheckCollisionAxis(collision, axis))
			return false;

		if (currentData.PenetrationDepth >= collision.Data.PenetrationDepth) {
			collision.Data = currentData;
		}
	}

	collision.Colliding = true;
	return true;
}

void Physics::CollisionDetection::GenContactPoints(Collision& collision)
{
	if (!collision.Colliding || collision.Data.PenetrationDepth >= 0.f)
	{
		return;
	}

	list<Vector3> polygonA, polygonB;
	vector<Plane> adjPlanesA, adjPlanesB;
	Vector3 normalA, normalB;

	collision.Pair.NodeA->GetCollisionShape()->GetIncidentReferencePolygon(collision.Data.CollisionNormal, polygonA, normalA, adjPlanesA);
	collision.Pair.NodeB->GetCollisionShape()->GetIncidentReferencePolygon(collision.Data.CollisionNormal, polygonB, normalB, adjPlanesB);

	if (polygonA.empty() || polygonB.empty())
	{
		return;
	}

	if (polygonA.size() == 1)
	{
		collision.Manifold = new Manifold();
		collision.Manifold->AddContact(
			polygonA.front(),
			polygonA.front() + collision.Data.CollisionNormal * collision.Data.PenetrationDepth,
			collision.Data.CollisionNormal,
			collision.Data.PenetrationDepth
		);
	}
	else if (polygonB.size() == 1)
	{
		collision.Manifold = new Manifold();
		collision.Manifold->AddContact(
			polygonB.front(),
			polygonB.front() + collision.Data.CollisionNormal * collision.Data.PenetrationDepth,
			collision.Data.CollisionNormal,
			collision.Data.PenetrationDepth
		);
	}

}

bool Physics::CollisionDetection::AddPossibleCollisionAxis(Collision& collision, Vector3 axis)
{
}

bool Physics::CollisionDetection::CheckCollisionAxis(Collision& collision, const Vector3& axis)
{
	//Overlap Test
	// Points go: 
	//          +-------------+
	//  +-------|-----+   2   |
	//  |   1   |     |       |
	//  |       +-----|-------+
	//  +-------------+
	//  A ------C --- B ----- D 
	//
	//	IF	 A < C AND B > C (Overlap in order object 1 -> object 2)
	//	IF	 C < A AND D > A (Overlap in order object 2 -> object 1)

	/* TUTORIAL 4 CODE */

	Vector3 min1, min2, max1, max2;

	// Get the min /max vertices along the axis from shape1 and shape2
	collision.Pair.NodeA->GetCollisionShape()->GetMinMaxVertexOnAxis(axis, min1, max1);
	collision.Pair.NodeB->GetCollisionShape()->GetMinMaxVertexOnAxis(axis, min2, max2);

	float A = Vector3::Dot(axis, min1);
	float B = Vector3::Dot(axis, max1);
	float C = Vector3::Dot(axis, min2);
	float D = Vector3::Dot(axis, max2);

	// Overlap Test ( Order : Object 1 -> Object 2)
	if (A <= C && B >= C) {
		collision.Data.CollisionNormal = axis;
		collision.Data.PenetrationDepth = C - B;
		// Smallest overlap distance is between B- >C
		// Compute closest point on edge of the object
		collision.Data.OverlapPoint = max1 + collision.Data.CollisionNormal * collision.Data.PenetrationDepth;

		return true;
	}

	// Overlap Test ( Order : Object 2 -> Object 1)
	if (C <= A && D >= A)
	{
		collision.Data.CollisionNormal = -axis;
		// Invert axis here so we can do all our resolution phase as
		// Object 1 -> Object 2
		collision.Data.PenetrationDepth = A - D;
		// Smallest overlap distance is between D- >A
		// Compute closest point on edge of the object
		collision.Data.OverlapPoint =
			min1 + collision.Data.CollisionNormal * collision.Data.PenetrationDepth;

		return true;
	}
	return false;
}
