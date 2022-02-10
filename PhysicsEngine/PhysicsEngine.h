#pragma once

#include "PhysicsNode.h"
#include <nclgl/TSingleton.h>
#include <vector>

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
		~PhysicsEngine();
		
		void UpdateBroadphase();
		void UpdateNarrowphase();

	private:

		float m_updateTimestep;
		std::vector<PhysicsNode*> m_physicsObjects;
		Vector3 m_gravity;
		WorldLimits m_worldLimits;

		OcTree* m_ocTree;
	};
}

