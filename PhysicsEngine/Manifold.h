//#pragma once
//#include <vector>
//
//#include "Utils/Vector3.h"
//
//namespace Physics
//{
//	struct ContactPoint
//	{
//		//Amount of additional energy to add to the system
//		// -- Summation of Baumgarte error correction and elasticity
//		float	b_term;
//
//		//Collision Normal and Penetration depth
//		Vector3 colNormal;
//		float	colPenetration;
//
//		Vector3 relPosA;			//Position relative to objectA
//		Vector3 relPosB;			//Position relative to objectB
//
//		//Solver - Total force added this frame
//		// - Used to clamp contact constraint over the course of the entire solver
//		//   to expected bounds.
//		float   sumImpulseContact;
//		Vector3 sumImpulseFriction;
//	};
//
//	class PhysicsNode;
//
//	class Manifold
//	{
//	public:
//		Manifold();
//		~Manifold();
//
//		//Initiate for collision pair
//		void Initiate(PhysicsNode* nodeA, PhysicsNode* nodeB);
//
//		//Called whenever a new collision contact between A & B are found
//		void AddContact(const Vector3& globalOnA, const Vector3& globalOnB, const Vector3& _normal, const float& _penetration);
//
//		//Sequentially solves each contact constraint
//		void ApplyImpulse();
//		void PreSolverStep(float dt);
//
//
//		//Debug draws the manifold surface area
//		void DebugDraw() const;
//
//		//Get the physics objects
//		PhysicsNode* NodeA() { return pnodeA; }
//		PhysicsNode* NodeB() { return pnodeB; }
//
//	protected:
//		void SolveContactPoint(ContactPoint& c);
//		void UpdateConstraint(ContactPoint& c);
//
//	public:
//		PhysicsNode* pnodeA;
//		PhysicsNode* pnodeB;
//		std::vector<ContactPoint>	contactPoints;
//	};
//}
//
//
