#include "PhysicsEngine.h"

#include "Manifold.h"
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

		if (m_partioning)
		{
			m_partioning->AddPhysicsNode(obj);
		}
	}

	void PhysicsEngine::RemovePhysicsObject(PhysicsNode* obj)
	{
		m_physicsObjects.erase(std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), obj), m_physicsObjects.end());

		if (m_partioning)
		{
			m_partioning->RemovePhysicsNode(obj);
		}
	}

	void PhysicsEngine::ClearObjects()
	{
		for(auto obj : m_physicsObjects)
		{
			m_partioning->RemovePhysicsNode(obj);
			delete obj;
		}

		m_physicsObjects.clear();
	}

	Vector3 PhysicsEngine::GetGravity()
	{
		return m_gravity;
	}

	float PhysicsEngine::GetDampingFactor()
	{
		return 0.01f;
	}

	PhysicsEngine::PhysicsEngine(): m_dtOffset(0)
	{
		m_gravity = Vector3(0.f, -9.81f, 0.f);

		m_worldLimits.Min = {-100.f, -100.f, -100.f};
		m_worldLimits.Max = {100.f, 100.f, 100.f};
		WorldPartitioning* tree = nullptr;// new OcTree(m_worldLimits.Min, m_worldLimits.Max, m_physicsObjects);
		m_partioning = std::unique_ptr<WorldPartitioning>(tree);
	}

	PhysicsEngine::~PhysicsEngine()
	{
		ClearObjects();
	}

	void PhysicsEngine::UpdatePhysics(float dt)
	{
		const float timestep = 1.f / 120.f;
		m_dtOffset += dt;

		if (m_dtOffset < timestep)
			return;

		m_dtOffset = 0;
		
		// Broadphase
		auto collisionPairs = GetBroadphaseCollisionPairs();

		// Narrowphase
		GetNarrowphaseCollisions(collisionPairs);

		ResolveCollisions();

		// Initialize Contraints

		// Update Velocities
		for (auto obj : m_physicsObjects)
		{
			obj->IntegrateAcceleration(timestep);
		}


		// Solve Constraints

		// Update Positions
		for (auto obj : m_physicsObjects)
		{
				obj->IntegrateVelocity(timestep);
		}

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

		return nodeA->GetPosition().DistSqr(nodeB->GetPosition()) < Maths::Squared(nodeA->GetBoundingRadius() + nodeB->GetBoundingRadius());
	}

	vector<CollisionPair> PhysicsEngine::GetBroadphaseCollisionPairs() const
	{
		if (!m_partioning)
		{
			vector<CollisionPair> result = {};
			for(size_t i = 0; i < m_physicsObjects.size() - 1; ++i)
			{
				for (size_t j = i + 1; j < m_physicsObjects.size(); ++j)
				{
					result.push_back(CollisionPair { m_physicsObjects[i], m_physicsObjects[j]});
				}
			}
			return result;
		}
		
		m_partioning->Update();
		return m_partioning->GetCollisionPairs();
	}

	void PhysicsEngine::GetNarrowphaseCollisions(vector<CollisionPair>& collisionPairs)
	{
		if (collisionPairs.empty())
		{
			return;
		}

		for(auto pair : collisionPairs)
		{
			Collision collision = Collision();
			if (CollisionDetection::ObjectsIntersecting(pair, collision))
			{
				collision.FramesLeft = m_numCollisionFrames;
				m_collisions.push_back(collision);
			}
		}


	}

	void PhysicsEngine::ResolveCollisions()
	{
		for(auto collision : m_collisions)
		{
			ResolveCollision(collision);
		}

		m_collisions.clear();
	}

	void PhysicsEngine::ResolveCollision(Collision& collision)
	{
		PhysicsNode* nodeA = collision.NodeA;
		PhysicsNode* nodeB = collision.NodeB;
		float collidingMass = nodeA->GetInverseMass() + nodeB->GetInverseMass();

		// Step 1: Set Position so that they no longer overlap
		nodeA->SetPosition(nodeA->GetPosition() - collision.Point.Normal * collision.Point.Penetration * (nodeA->GetInverseMass() / collidingMass));
		nodeB->SetPosition(nodeB->GetPosition() - collision.Point.Normal * collision.Point.Penetration * (nodeB->GetInverseMass() / collidingMass));

		// Step 2: calculate velocities
		Vector3 contactVelocity = nodeB->GetLinearVelocity() - nodeA->GetLinearVelocity();

		// Step 3: Apply Force
		float forceMagnitude = Vector3::Dot(contactVelocity, collision.Point.Normal);
		Vector3 force = collision.Point.Normal * forceMagnitude;

		nodeA->SetLinearVelocity(Vector3::Zero());
		nodeA->ApplyImpulse(force);
		nodeB->SetLinearVelocity(Vector3::Zero());
		nodeB->ApplyImpulse(-force);

		//TODO: Take into account rotational velocities etc.
	}
}
