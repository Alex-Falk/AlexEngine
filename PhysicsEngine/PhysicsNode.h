#pragma once

#include <functional>
#include <nclgl/Matrix4.h>
#include <nclgl/Quaternion.h>
#include "common.h"

class CollisionShape;

namespace  Physics
{
	typedef std::function<void(const Matrix4& transform)> UpdateCallback;

	class PhysicsNode
	{
	public:
		PhysicsNode(Vector3 initialPos, float inverseMass, float boundingRadius, bool applyGravity);

		void Integrate(float dt);

		void ApplyForce(Vector3 force);
		void ApplyLinearVelocity(Vector3 velocity);
		void SetPosition(Vector3 position);

		void ApplyTorque(Vector3 torque);
		void ApplyAngularVelocity(Vector3 angularVelocity);
		void SetRotation(Quaternion rotation);

		void SetInverseMass(float inverseMass);

		void SetGravityEnabled(bool enabled);

		void SetOnUpdateCallback(UpdateCallback callback) { m_onUpdateCallback = callback; }
		void FireOnUpdateCallback();

		Vector3 GetPosition() const { return m_position; }
		float GetBoundingRadius() const { return m_boundingRadius; }
		Vector3 GetLinearVelocity();

		CollisionShape* GetCollisionShape();
		bool HasCollision();
	
	protected:

	private:
		Matrix4 m_worldTransform;

		Vector3 m_position;
		Vector3 m_linearVelocity;
		Vector3 m_force;
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

	};
}

