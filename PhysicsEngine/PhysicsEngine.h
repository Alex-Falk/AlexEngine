#pragma once

#include "PhysicsObject.h"
#include <GraphicsEngine/TSingleton.h>
#include <vector>

class PhysicsEngine : TSingleton<PhysicsEngine>
{
public:

	void AddPhysicsObject(PhysicsObject* obj);
	void RemovePhysicsObject(PhysicsObject* obj);

	void ClearObjects();

protected:
	PhysicsEngine();
	~PhysicsEngine();

	void UpdatePhysics();

	void UpdateBroadphase();
	void UpdateNarrowphase();

private:

	float m_updateTimestep;
	std::vector<PhysicsObject*> m_physicsObjects;
	Vector3 m_gravity;
};

