#include "PhysicsEngine.h"

#include "nclgl/NCLDebug.h"

void PhysicsEngine::AddPhysicsObject(PhysicsNode* obj)
{
	if (!obj)
	{
		NCLERROR("Tried to add a nullptr PhysicsNode");
	}

	m_physicsObjects.push_back(obj);
}

void PhysicsEngine::RemovePhysicsObject(PhysicsNode* obj)
{
	m_physicsObjects.erase(std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), obj), m_physicsObjects.end());
}

void PhysicsEngine::ClearObjects()
{
	for(auto obj : m_physicsObjects)
	{
		SAFE_DELETE(obj);
	}

	m_physicsObjects.clear();
}

Vector3 PhysicsEngine::GetGravity()
{
	return m_gravity;
}

float PhysicsEngine::GetDampingFactor()
{
	return 0.1f;
}

PhysicsEngine::PhysicsEngine()
{
	m_gravity = Vector3(0.f, -9.81f, 0.f);
}

PhysicsEngine::~PhysicsEngine()
{
	ClearObjects();
}

void PhysicsEngine::UpdatePhysics(float dt)
{
	for (auto obj : m_physicsObjects)
	{
		obj->Integrate(dt);
	}
}

void PhysicsEngine::UpdateBroadphase()
{
}

void PhysicsEngine::UpdateNarrowphase()
{
}
