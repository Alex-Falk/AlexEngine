#pragma once

#include "Node.h"
#include <nclgl/TSingleton.h>
#include <vector>

namespace Physics
{
	class PhysicsEngine : public TSingleton<PhysicsEngine>
	{
		friend class TSingleton<PhysicsEngine>;

	public:

		void AddPhysicsObject(Node* obj);
		void RemovePhysicsObject(Node* obj);

		void ClearObjects();

		Vector3 GetGravity();
		float GetDampingFactor();

		void UpdatePhysics(float dt);

		std::vector<Node*> GetPhysicsNodes();


	protected:
		PhysicsEngine();
		~PhysicsEngine();



		void UpdateBroadphase();
		void UpdateNarrowphase();

	private:

		float m_updateTimestep;
		std::vector<Node*> m_physicsObjects;
		Vector3 m_gravity;
	};
}

