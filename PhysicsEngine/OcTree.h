#pragma once
#include "common.h"
#include "nclgl/BoundingBox.h"
#include "nclgl/TSingleton.h"

namespace Physics
{
	class Node;

	class OcTree : TSingleton<OcTree>
	{
		struct Node
		{
			Node* Parent = nullptr;
			Node** Children;

			BoundingBox* AABB;

			vector<Physics::Node*> PhysicsNodes;
		};

		Node* root = nullptr;

		OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax, std::vector<Physics::Node*>* physicsNodes);
		OcTree(Vector3 min, Vector3 max, std::vector<Physics::Node*>* physicsNodes);
		~OcTree();

		void TerminateTree(Node** node);

		void SplitNode(Node* node);

	private:
		std::vector<Physics::CollisionPair> CreateCollisionPairsForNode(Node* node);
		std::vector<Physics::Node*> GetPhysicsNodesInNode(Node* node, std::vector<Physics::Node*> parentPhysicsNode);
		void UpdateTree();
		void CheckPhysicsNodesToUpdate(Node * node);
		void CombineChildren(Node* node);

		std::vector<Physics::Node*> m_nodesToUpdate;
		std::vector<Physics::Node*>* m_physicsNodes;
		Node* m_root;
	};
}
