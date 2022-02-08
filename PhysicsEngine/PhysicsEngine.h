#pragma once

#include "PhysicsNode.h"
#include <nclgl/TSingleton.h>
#include <vector>

namespace Physics
{
	class PhysicsEngine : public TSingleton<PhysicsEngine>
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


	protected:
		PhysicsEngine();
		~PhysicsEngine();



		void UpdateBroadphase();
		void UpdateNarrowphase();

	private:

		float m_updateTimestep;
		std::vector<PhysicsNode*> m_physicsObjects;
		Vector3 m_gravity;
	};
}

