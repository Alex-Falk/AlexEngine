#include "PhysicsNode.h"

#include "PhysicsEngine.h"

void PhysicsNode::Integrate(const float dt)
{
	if (m_inverseMass > 0.f && m_applyGravity)
	{
		m_linearVelocity = PhysicsEngine::Instance()->GetGravity() * m_inverseMass * dt;
	}

	Vector3 v1 = m_linearVelocity;
	Vector3 v2 = v1 + (m_force * m_inverseMass * dt * .5f);
	Vector3 v3 = v2 + (m_force * m_inverseMass * dt * .5f);
	Vector3 v4 = v3 + (m_force * m_inverseMass * dt);

	const Vector3 linearHalfVelocity = m_linearVelocity + (v1 + (v2 + v3) * 2.f + v4) * (1.f / 6.f) * dt *
		PhysicsEngine::Instance()->GetDampingFactor();
	m_linearVelocity += m_force * m_inverseMass * dt;
	m_linearVelocity = m_linearVelocity * PhysicsEngine::Instance()->GetDampingFactor();
	m_position += linearHalfVelocity * dt;

	v1 = m_angularVelocity * PhysicsEngine::Instance()->GetDampingFactor();
	v2 = v1 + (m_inverseInertia * m_torque * dt * .5f);
	v3 = v2 + (m_inverseInertia * m_torque * dt * .5f);
	v4 = v3 + (m_inverseInertia * m_torque * dt);

	Vector3 angularHalfVelocity = (v1 + (v2 + v3) * 2.f + v4) * (dt / 6.f);
	angularHalfVelocity = m_angularVelocity + angularHalfVelocity * PhysicsEngine::Instance()->GetDampingFactor();

	m_angularVelocity += m_inverseInertia * m_torque * dt;
	m_angularVelocity = m_angularVelocity * PhysicsEngine::Instance()->GetDampingFactor();
	m_orientation = m_orientation + Quaternion(angularHalfVelocity * dt * .5f, 0.f) * m_orientation;
	m_orientation.Normalise();

	FireOnUpdateCallback();
}

void PhysicsNode::ApplyForce(Vector3 force)
{
	m_force += force;
}

void PhysicsNode::ApplyLinearVelocity(Vector3 velocity)
{
	m_linearVelocity += velocity;
}

void PhysicsNode::SetPosition(Vector3 position)
{
	m_position = position;
}

void PhysicsNode::ApplyTorque(Vector3 torque)
{
	m_torque += torque;
}

void PhysicsNode::ApplyAngularVelocity(Vector3 angularVelocity)
{
	m_angularVelocity += angularVelocity;
}

void PhysicsNode::SetRotation(Quaternion rotation)
{
	m_orientation = rotation;
}

void PhysicsNode::SetInverseMass(float inverseMass)
{
	m_inverseMass = inverseMass;
}

void PhysicsNode::SetGravityEnabled(bool enabled)
{
	m_applyGravity = enabled;
}

void PhysicsNode::FireOnUpdateCallback()
{
	m_worldTransform = m_orientation.ToMatrix4();
	m_worldTransform.SetPositionVector(m_position);

	if (m_onUpdateCallback)
	{
		m_onUpdateCallback(m_worldTransform);
	}
}
