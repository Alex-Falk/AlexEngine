#pragma once

#include "nclgl/BoundingBox.h"
#include "nclgl/TSingleton.h"

namespace Physics
{
	class PhysicsNode;
	class CollisionPair;

	class OcTree
	{
		struct Node
		{
			Node();

			Node* Parent = nullptr;
			Node** Children;

			BoundingBox* AABB;

			vector<PhysicsNode*> PhysicsNodes;
			vector<Physics::PhysicsNode*> GetAllPhysicsNodesInChildren();
			size_t GetNumberOfPhysicsNodes() const;
		};

	public:
		Node* root = nullptr;

		OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax, std::vector<PhysicsNode*> physicsNodes);
		OcTree(Vector3 min, Vector3 max, std::vector<Physics::PhysicsNode*> physicsNodes);
		~OcTree();

		
		static void SplitNode(Node* node, vector<PhysicsNode*> physicsNodesToAssign);

		void AddPhysicsNode(PhysicsNode* physicsNode) const;
		void RemovePhysicsNode(PhysicsNode* physicsNode) const;
	private:
		void UpdateTree();
		void UpdatePhysicsNodes();
		void AdjustNodesPostUpdate() const;

		static void TerminateTree(Node* node);
		static void TryAddPhysicsNode(Node* node, PhysicsNode* physNode);
		static void TryRemovePhysicsNode(Node* node, PhysicsNode* physNode);
		static void CollapseNode(Node* node);
		static void CheckAdjustNode(Node* node);
		void CheckPhysicsNodesToUpdate(Node* node);

		static vector<CollisionPair> CreateCollisionPairs(Node* node);
		static vector<PhysicsNode*> GetPhysicsNodes(const Node* node, const vector<PhysicsNode*>& elementsInParent);

		static bool IsPhysicsNodeInNode(Node* node, PhysicsNode* physicsNode);

		std::vector<PhysicsNode*> m_movedNodes;
		std::vector<PhysicsNode*> m_addedNodes;
		std::vector<PhysicsNode*> m_removedNodes;
		std::vector<PhysicsNode*> m_physicsNodes;
		Node* m_root;
	};
}
