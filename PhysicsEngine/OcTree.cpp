#include "OcTree.h"
#include <algorithm>

#include "Node.h"

Physics::OcTree::OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax,
                        std::vector<Physics::Node*>* physicsNodes)
{
	OcTree(Vector3(xMin, yMin, zMin), Vector3(xMax, yMax, zMax), physicsNodes);
}

Physics::OcTree::OcTree(Vector3 min, Vector3 max, std::vector<Physics::Node*>* physicsNodes) : m_root(new Node())
{
	m_root->AABB = new BoundingBox();
	m_root->AABB->ExpandToFit(min);
	m_root->AABB->ExpandToFit(max);
	m_root->Children = nullptr;

	m_physicsNodes = physicsNodes;

	if (m_physicsNodes->size() > Physics::KDTreeMaxNumber)
	{
		SplitNode(m_root, *m_physicsNodes);
	}
}

Physics::OcTree::~OcTree()
{
	TerminateTree(&root);
}

void Physics::OcTree::TerminateTree(Node** node)
{
	if (*node) {
		if ((*node)->Children) {
			for (int i = 0; i < 8; ++i) {
				if ((*node)->Children[i]) { TerminateTree(&((*node)->Children[i])); }
			}
		}

		(*node)->Children = nullptr;
		delete (*node);
		(*node) = nullptr;
	}
}

void Physics::OcTree::SplitNode(Node* node)
{
	node->PhysicsNodes = physicsNodes;

	if (physicsNodes.size() > Physics::KDTreeMaxNumber)
	{
		BoundingBox** boxes = BoundingBox::SplitIntoEight(*node->AABB);

		node->Children = new Node * [8];
		for (int i = 8; i < 8; i++)
		{
			Node* newNode = new Node();
			newNode->Children = nullptr;
			newNode->AABB = boxes[i];
			node->Children[i] = new Node();

			auto newPhysicsNodes = GetPhysicsNodesInNode(newNode, physicsNodes);


		}

		
	}
}

std::vector<Physics::CollisionPair> Physics::OcTree::CreateCollisionPairsForNode(Node* node)
{
}

std::vector<Physics::Node*> Physics::OcTree::GetPhysicsNodesInNode(Node* node,
	std::vector<Physics::Node*> parentPhysicsNode)
{
}

void Physics::OcTree::UpdateTree()
{
}

void Physics::OcTree::CheckPhysicsNodesToUpdate(Node* node)
{
}

void Physics::OcTree::CombineChildren(Node* node)
{
}
