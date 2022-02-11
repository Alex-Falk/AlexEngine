#pragma once
#include <list>
#include <vector>

class Plane;
class Vector3;

namespace Physics
{
	class PhysicsNode;
	
	class CollisionShape
	{
	public:
		enum Type
		{
			None = 0,
			AABB = 1,
			Sphere = 2,
			Max = 4,
		};

		virtual ~CollisionShape() = default;

		virtual void GetCollisionAxes(
			const PhysicsNode* otherObject,
			std::vector<Vector3>& out_axes) const = 0;

		virtual void GetMinMaxVertexOnAxis(
			const Vector3& axis,
			Vector3& out_min,
			Vector3& out_max) const = 0;

		virtual void GetIncidentReferencePolygon(
			const Vector3& axis,
			std::list<Vector3>& out_face,
			Vector3& out_normal,
			std::vector<Plane>& out_adjacent_planes) const = 0;

		virtual Type GetType() { return None; }
	};

	class SphereCollisionShape : public CollisionShape
	{
		
	public:
		SphereCollisionShape(float radius);

		Type GetType() override { return Sphere; }

		void GetCollisionAxes(const PhysicsNode* otherObject, std::vector<Vector3>& out_axes) const override;
		void GetMinMaxVertexOnAxis(const Vector3& axis, Vector3& out_min, Vector3& out_max) const override;
		void GetIncidentReferencePolygon(const Vector3& axis, std::list<Vector3>& out_face, Vector3& out_normal,
			std::vector<Plane>& out_adjacent_planes) const override;

		float GetRadius() const { return m_radius; }

	private:
		float m_radius;
	};

	class AABBCollisionShape : public CollisionShape
	{
		Type GetType() override { return AABB; }
	};
}
