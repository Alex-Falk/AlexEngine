#include "PhysicsEngine.h"

#include "OcTree.h"
#include "nclgl/NCLDebug.h"
#include "Maths/Math.h"
#include "OcTree.h"

namespace Physics
{
	void PhysicsEngine::AddPhysicsObject(PhysicsNode* obj)
	{
		if (!obj)
		{
			NCLERROR("Tried to add a nullptr PhysicsNode");
		}

		m_physicsObjects.push_back(obj);

		if (m_ocTree)
		{
			m_ocTree->AddPhysicsNode(obj);
		}
	}

	void PhysicsEngine::RemovePhysicsObject(PhysicsNode* obj)
	{
		m_physicsObjects.erase(std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), obj), m_physicsObjects.end());

		if (m_ocTree)
		{
			m_ocTree->RemovePhysicsNode(obj);
		}
	}

	void PhysicsEngine::ClearObjects()
	{
		for(auto obj : m_physicsObjects)
		{
			m_ocTree->RemovePhysicsNode(obj);
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

		m_worldLimits.Min = { -100.f, -100.f, -100.f };
		m_worldLimits.Max = { 100.f, 100.f, 100.f };
		m_ocTree = new OcTree(m_worldLimits.Min, m_worldLimits.Max, m_physicsObjects);
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

		
		// Broadphase
		auto collisionPairs = GetBroadphaseCollisionPairs();

		// Narrowphase

		// Initialize Contraints

		// Update Velocities

		// Solve Constraints

		// Update Positions
	}

	std::vector<PhysicsNode*> PhysicsEngine::GetPhysicsNodes()
	{
		return m_physicsObjects;
	}

	bool PhysicsEngine::PhysicsNodeSpheresOverlap(PhysicsNode* nodeA, PhysicsNode* nodeB)
	{
		if (!nodeA || !nodeB)
		{
			NCLERROR("One or both PhysicsNodes in PhysicsNodeSpheresOverlap is null");
			return false;
		}

		return nodeA->GetPosition().DistSqr(nodeB->GetPosition()) < Math::Squared(nodeA->GetBoundingRadius() + nodeB->GetBoundingRadius());
	}

	vector<CollisionPair> PhysicsEngine::GetBroadphaseCollisionPairs() const
	{
		m_ocTree->UpdateTree();
		return m_ocTree->GetCollisionPairs();
	}

	void PhysicsEngine::HandleNarrowphaseCollisions(vector<CollisionPair>& collisionPairs)
	{
		if (collisionPairs.empty())
		{
			return;
		}



	}


}