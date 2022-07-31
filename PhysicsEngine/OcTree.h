#pragma once

#include "WorldPartitioning.h"
#include "nclgl/BoundingBox.h"

namespace Physics
{
	class PhysicsNode;
	struct CollisionPair;

	class OcTree : public WorldPartitioning
	{
		struct Node
		{
			Node();

			Node* Parent = nullptr;
			Node** Children;

			BoundingBox* AABB;

			vector<PhysicsNode*> PhysicsNodes;
			vector<PhysicsNode*> GetAllPhysicsNodesInChildren();
			size_t GetNumberOfPhysicsNodes() const;
		};

	public:
		OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax,
		       std::vector<PhysicsNode*> physicsNodes);
		OcTree(Vector3 min, Vector3 max, std::vector<PhysicsNode*> physicsNodes);
		~OcTree() override;


		void AddPhysicsNode(PhysicsNode* physicsNode) const override;
		void RemovePhysicsNode(PhysicsNode* physicsNode) const override;
		vector<CollisionPair> GetCollisionPairs() const override;

		void Update() override;
	private:
		void UpdatePhysicsNodes();
		void AdjustNodesPostUpdate() const;

		static void TerminateTree(Node* node);
		static void TryAddPhysicsNode(Node* node, PhysicsNode* physNode);
		static void TryRemovePhysicsNode(Node* node, PhysicsNode* physNode);
		static void CollapseNode(Node* node);
		static void CheckAdjustNode(Node* node);
		static void SplitNode(Node* node, const vector<PhysicsNode*>& physicsNodesToAssign);
		void CheckPhysicsNodesToUpdate(Node* node);

		static vector<CollisionPair> CreateCollisionPairs(Node* node);
		static vector<PhysicsNode*> GetPhysicsNodes(const Node* node, const vector<PhysicsNode*>& elementsInParent);

		static bool IsPhysicsNodeInNode(Node* node, const PhysicsNode* physicsNode);

		std::vector<PhysicsNode*> m_movedNodes;
		std::vector<PhysicsNode*> m_addedNodes;
		std::vector<PhysicsNode*> m_removedNodes;
		std::vector<PhysicsNode*> m_physicsNodes;
		Node* m_root;
	};
}
