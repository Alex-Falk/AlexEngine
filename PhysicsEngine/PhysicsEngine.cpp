#include "PhysicsEngine.h"

#include "nclgl/NCLDebug.h"

void Physics::PhysicsEngine::AddPhysicsObject(PhysicsNode* obj)
{
	if (!obj)
	{
		NCLERROR("Tried to add a nullptr PhysicsNode");
	}

	m_physicsObjects.push_back(obj);
}

void Physics::PhysicsEngine::RemovePhysicsObject(PhysicsNode* obj)
{
	m_physicsObjects.erase(std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), obj), m_physicsObjects.end());
}

void Physics::PhysicsEngine::ClearObjects()
{
	for(auto obj : m_physicsObjects)
	{
		SAFE_DELETE(obj);
	}

	m_physicsObjects.clear();
}

Vector3 Physics::PhysicsEngine::GetGravity()
{
	return m_gravity;
}

float Physics::PhysicsEngine::GetDampingFactor()
{
	return 0.1f;
}

Physics::PhysicsEngine::PhysicsEngine()
{
	m_gravity = Vector3(0.f, -9.81f, 0.f);
}

Physics::PhysicsEngine::~PhysicsEngine()
{
	ClearObjects();
}

void Physics::PhysicsEngine::UpdatePhysics(float dt)
{
	for (auto obj : m_physicsObjects)
	{
		obj->Integrate(dt);
	}


	// Broadphase

	// Narrowphase

	// Initialize Contraints

	// Update Velocities

	// Solve Constraints

	// Update Positions
}

std::vector<Physics::PhysicsNode*> Physics::PhysicsEngine::GetPhysicsNodes()
{
	return m_physicsObjects;
}

void Physics::PhysicsEngine::UpdateBroadphase()
{
}

void Physics::PhysicsEngine::UpdateNarrowphase()
{
}
