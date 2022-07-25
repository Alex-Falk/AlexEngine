#pragma once

#include <functional>
#include <nclgl/Matrix4.h>
#include <nclgl/Quaternion.h>

#include "CollisionShape.h"
#include "common.h"

namespace  Physics
{
	class CollisionShape;

	typedef std::function<void(const Matrix4& transform)> UpdateCallback;

	class PhysicsNode
	{
	public:
		PhysicsNode(const Vector3& initialPos, float inverseMass, float boundingRadius, bool applyGravity);
		
		void IntegrateAcceleration(float dt);
		void IntegrateVelocity(float dt);

		void ApplyForce(Vector3 force);
		void ApplyLinearVelocity(Vector3 velocity);
		void SetPosition(Vector3 position);
		void ApplyImpulse(Vector3 impulse);
		void SetLinearVelocity(Vector3 velocity);

		void ApplyTorque(Vector3 torque);
		void ApplyAngularVelocity(Vector3 angularVelocity);
		void SetRotation(Quaternion rotation);

		void SetInverseMass(float inverseMass);
		void SetCollisionShape(CollisionShape* collisionShape);

		void SetGravityEnabled(bool enabled);

		void SetOnUpdateCallback(UpdateCallback callback) { m_onUpdateCallback = callback; }
		void FireOnUpdateCallback();

		inline Vector3 GetPosition() const { return m_position; }
		float GetBoundingRadius() const { return m_boundingRadius; }
		float GetInverseMass() const { return m_inverseMass; }
		Vector3 GetLinearVelocity();
		CollisionShape* GetCollisionShape() { return m_collisionShape; }
		bool HasCollision() const;

		Matrix4& GetWorldTransform() { return m_worldTransform; }
	
	protected:

	private:
		Matrix4 m_worldTransform;

		Vector3 m_position;
		Vector3 m_linearVelocity;
		Vector3 m_force;
		Vector3 m_impulse;
		float m_inverseMass;

		Quaternion m_orientation;
		Vector3 m_angularVelocity;
		Vector3 m_torque;
		Matrix3 m_inverseInertia;

		float m_elasticity{};
		float m_friction{};
		float m_boundingRadius;

		bool m_applyGravity;

		Physics::Integrator m_integrator;
		UpdateCallback m_onUpdateCallback;

		CollisionShape* m_collisionShape;

		Vector3 m_linearHalfVelocity;
		Vector3 m_angularHalfVelocity;

	};
}

