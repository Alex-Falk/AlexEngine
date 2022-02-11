#include "CollisionShape.h"

Physics::SphereCollisionShape::SphereCollisionShape(float radius) : m_radius(radius)
{
}

void Physics::SphereCollisionShape::GetCollisionAxes(const PhysicsNode* otherObject,
                                                     std::vector<Vector3>& out_axes) const
{
}

void Physics::SphereCollisionShape::GetMinMaxVertexOnAxis(const Vector3& axis, Vector3& out_min, Vector3& out_max) const
{
}

void Physics::SphereCollisionShape::GetIncidentReferencePolygon(const Vector3& axis, std::list<Vector3>& out_face,
	Vector3& out_normal, std::vector<Plane>& out_adjacent_planes) const
{
}
