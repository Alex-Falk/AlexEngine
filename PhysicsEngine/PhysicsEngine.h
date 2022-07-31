#pragma once

#include "PhysicsNode.h"
#include <nclgl/TSingleton.h>
#include <vector>

#include "CollisionDetection.h"
#include "OcTree.h"

namespace Physics
{
	struct WorldLimits
	{
		Vector3 Min;
		Vector3 Max;
	};

	struct CollisionPair
	{
		PhysicsNode* NodeA;
		PhysicsNode* NodeB;

		bool IsValid() const { return NodeA != nullptr && NodeB != nullptr && NodeA != NodeB; }
	};


	class PhysicsEngine final : public TSingleton<PhysicsEngine>
	{
		friend class TSingleton<PhysicsEngine>;

	public:
		void AddPhysicsObject(PhysicsNode* obj);
		void RemovePhysicsObject(PhysicsNode* obj);

		void ClearObjects();

		Vector3 GetGravity();
		float GetDampingFactor();

		void UpdatePhysics(float dt);

		std::vector<PhysicsNode*> GetPhysicsNodes();

		static bool PhysicsNodeSpheresOverlap(PhysicsNode* nodeA, PhysicsNode* nodeB);

	protected:
		PhysicsEngine();
		~PhysicsEngine() override;

		vector<CollisionPair> GetBroadphaseCollisionPairs() const;
		void GetNarrowphaseCollisions(vector<CollisionPair>& collisionPairs);
		void ResolveCollisions();

		static void ResolveCollision(Collision& collision);

	private:
		float m_dtOffset;
		std::vector<PhysicsNode*> m_physicsObjects;
		std::vector<Collision> m_collisions;
		Vector3 m_gravity;
		WorldLimits m_worldLimits;

		std::unique_ptr<WorldPartitioning> m_partioning;

		CollisionDetection m_collisionDetection;

		const uint16_t m_numCollisionFrames = 5;
	};
}
