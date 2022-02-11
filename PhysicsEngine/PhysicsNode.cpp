#include "PhysicsNode.h"

#include "CollisionShape.h"
#include "PhysicsEngine.h"

Physics::PhysicsNode::PhysicsNode(const Vector3 initialPos, const float inverseMass, const float boundingRadius, const bool applyGravity)
	: m_position(initialPos), m_inverseMass(inverseMass), m_boundingRadius(boundingRadius),
	  m_applyGravity(applyGravity), m_integrator(Integrator::RK4)
{
	FireOnUpdateCallback();
}

void Physics::PhysicsNode::IntegrateAcceleration(float dt)
{
	if (m_inverseMass > 0.f && m_applyGravity)
	{
		m_linearVelocity = PhysicsEngine::Instance()->GetGravity() * m_inverseMass * dt;
	}

	Vector3 v1 = m_linearVelocity;
	Vector3 v2 = v1 + (m_force * m_inverseMass * dt * .5f);
	Vector3 v3 = v2 + (m_force * m_inverseMass * dt * .5f);
	Vector3 v4 = v3 + (m_force * m_inverseMass * dt);

	m_linearHalfVelocity = m_linearVelocity + (v1 + (v2 + v3) * 2.f + v4) * (1.f / 6.f) * dt *
		PhysicsEngine::Instance()->GetDampingFactor();
	m_linearVelocity += m_force * m_inverseMass * dt;
	m_linearVelocity = m_linearVelocity * PhysicsEngine::Instance()->GetDampingFactor();


	v1 = m_angularVelocity * PhysicsEngine::Instance()->GetDampingFactor();
	v2 = v1 + (m_inverseInertia * m_torque * dt * .5f);
	v3 = v2 + (m_inverseInertia * m_torque * dt * .5f);
	v4 = v3 + (m_inverseInertia * m_torque * dt);

	m_angularHalfVelocity = (v1 + (v2 + v3) * 2.f + v4) * (dt / 6.f);
	m_angularHalfVelocity = m_angularVelocity + m_angularHalfVelocity * PhysicsEngine::Instance()->GetDampingFactor();

	m_angularVelocity += m_inverseInertia * m_torque * dt;
	m_angularVelocity = m_angularVelocity * PhysicsEngine::Instance()->GetDampingFactor();


}

void Physics::PhysicsNode::IntegrateVelocity(float dt)
{
	m_position += m_linearHalfVelocity * dt;

	m_orientation = m_orientation + Quaternion(m_angularHalfVelocity * dt * .5f, 0.f) * m_orientation;
	m_orientation.Normalise();

	FireOnUpdateCallback();
}


void Physics::PhysicsNode::ApplyForce(Vector3 force)
{
	m_force += force;
}

void Physics::PhysicsNode::ApplyLinearVelocity(Vector3 velocity)
{
	m_linearVelocity += velocity;
}

void Physics::PhysicsNode::SetPosition(Vector3 position)
{
	m_position = position;
}

void Physics::PhysicsNode::ApplyTorque(Vector3 torque)
{
	m_torque += torque;
}

void Physics::PhysicsNode::ApplyAngularVelocity(Vector3 angularVelocity)
{
	m_angularVelocity += angularVelocity;
}

void Physics::PhysicsNode::SetRotation(Quaternion rotation)
{
	m_orientation = rotation;
}

void Physics::PhysicsNode::SetInverseMass(float inverseMass)
{
	m_inverseMass = inverseMass;
}

void Physics::PhysicsNode::SetCollisionShape(CollisionShape* collisionShape)
{
	m_collisionShape = collisionShape;
}

void Physics::PhysicsNode::SetGravityEnabled(bool enabled)
{
	m_applyGravity = enabled;
}

void Physics::PhysicsNode::FireOnUpdateCallback()
{
	m_worldTransform = m_orientation.ToMatrix4();
	m_worldTransform.SetPositionVector(m_position);

	if (m_onUpdateCallback)
	{
		m_onUpdateCallback(m_worldTransform);
	}
}

Vector3 Physics::PhysicsNode::GetLinearVelocity()
{
	return m_linearVelocity;
}

bool Physics::PhysicsNode::HasCollision() const
{
	return m_collisionShape != nullptr;
}
