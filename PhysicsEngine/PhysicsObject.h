#pragma once

#include <MathLibrary/Matrix4.h>
#include <GraphicsEngine/Quaternion.h>
#include "common.h"

class PhysicsObject
{
public:

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

	float m_elasticity;
	float m_friction;

	Physics::Integrator m_integrator;
};

