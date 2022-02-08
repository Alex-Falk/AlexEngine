#pragma once
#include "common.h"
#include "nclgl/BoundingBox.h"
#include "nclgl/TSingleton.h"

namespace Physics
{
	class PhysicsNode;

	class OcTree : TSingleton<OcTree>
	{
		struct Node
		{
			Node();

			Node* Parent = nullptr;
			Node** Children{};

			BoundingBox* AABB{};

			vector<PhysicsNode*> PhysicsNodes;
			vector<Physics::PhysicsNode*> GetAllPhysicsNodesInChildren();
			size_t GetNumberOfPhysicsNodes() const;
		};

	public:
		Node* root = nullptr;

		OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax, std::vector<PhysicsNode*> physicsNodes);
		OcTree(Vector3 min, Vector3 max, std::vector<Physics::PhysicsNode*> physicsNodes);
		~OcTree();

		void TerminateTree(Node** node);

		static void SplitNode(Node* node, vector<PhysicsNode*> physicsNodesToAssign);

		void AddPhysicsNode(PhysicsNode* physicsNode);
		void RemovePhysicsNode(PhysicsNode* physicsNode);
	private:
		static std::vector<Physics::CollisionPair> CreateCollisionPairsForNode(Node* node);
		static std::vector<Physics::PhysicsNode*> GetPhysicsNodesInNode(const Node* node, const std::vector<PhysicsNode*>& elementsInParent);
		void UpdateTree();
		void UpdatePhysicsNodes();
		void AdjustNodesPostUpdate();

		void CheckPhysicsNodesToUpdate(Node * node);
		static void TryAddPhysicsNode(Node* node, PhysicsNode* physNode);
		static void TryRemovePhysicsNode(Node* node, PhysicsNode* physNode);
		void CollapseNode(Node* node);
		void CheckAdjustNode(Node* node);

		static bool IsPhysicsNodeInNode(Node* node, PhysicsNode* physicsNode);

		std::vector<PhysicsNode*> m_movedNodes;
		std::vector<PhysicsNode*> m_addedNodes;
		std::vector<PhysicsNode*> m_removedNodes;
		std::vector<PhysicsNode*> m_physicsNodes;
		Node* m_root{};
	};
}
