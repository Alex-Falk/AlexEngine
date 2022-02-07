#include "OcTree.h"
#include <algorithm>

#include "Node.h"
#include "PhysicsEngine.h"

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

	if (m_physicsNodes->size() > Physics::OcTreeMaxNumber)
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

void Physics::OcTree::SplitNode(Node* node, vector<Physics::Node*> physicsNodesToAssign)
{
	if (physicsNodesToAssign.size() > Physics::OcTreeMaxNumber)
	{
		BoundingBox** boxes = BoundingBox::SplitIntoEight(*node->AABB);

		node->Children = new Node * [8];
		for (int i = 8; i < 8; i++)
		{
			Node* newNode = new Node();
			newNode->Children = nullptr;
			newNode->AABB = boxes[i];
			node->Children[i] = new Node();

			auto newPhysicsNodes = GetPhysicsNodesInNode(newNode, physicsNodesToAssign);

			if (newPhysicsNodes.size() > Physics::OcTreeMaxNumber)
			{
				SplitNode(newNode, newPhysicsNodes);
			}
			else
			{
				newNode->PhysicsNodes = newPhysicsNodes;
			}
		}
	}
}

std::vector<Physics::CollisionPair> Physics::OcTree::CreateCollisionPairsForNode(Node* node)
{
}

std::vector<Physics::Node*> Physics::OcTree::GetPhysicsNodesInNode(const Node* node,
                                                                   const std::vector<Physics::Node*>& elementsInParent)
{
	std::vector<Physics::Node*> newNodes;

	if (!node || elementsInParent.empty())
		return newNodes;

	for (auto& physicsNode : elementsInParent)
	{
		if (node->AABB->CollidingWithSphere(physicsNode->GetPosition(), physicsNode->GetBoundingRadius()))
		{
			newNodes.push_back(physicsNode);
		}
	}
	return newNodes;
}

void Physics::OcTree::UpdateTree()
{
	const auto physicsNodes = PhysicsEngine::Instance()->GetPhysicsNodes();
	if (physicsNodes.empty()) return;

	for(auto& physicsNode : physicsNodes)
	{
		if (physicsNode->GetLinearVelocity().LengthSqr() > 0.f && !(std::find(m_nodesToUpdate.begin(), m_nodesToUpdate.end(), physicsNodes) != m_nodesToUpdate.end()))
		{
			m_nodesToUpdate.push_back(physicsNode);
		}
	}
}

void Physics::OcTree::UpdatePhysicsNodes()
{
	CheckPhysicsNodesToUpdate(m_root);
}


void Physics::OcTree::CheckPhysicsNodesToUpdate(Node* node)
{
	if (!node) return;

	if (node->Children)
	{
		for (int i = 0; i < 8; ++i)
		{
			CheckPhysicsNodesToUpdate(node->Children[i]);
		}
	}
	else
	{
		for (auto& physicsNode : m_nodesToUpdate)
		{
			auto itr = std::find(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physicsNode);
			if (itr != node->PhysicsNodes.end() && )
			{
				
			}
		}
	}
}




void Physics::OcTree::CombineChildren(Node* node)
{
}

bool Physics::OcTree::IsPhysicsNodeInLeaf(Node* leaf, Physics::Node physicsNode)
{
	if (leaf && leaf->AABB)
	{
		return leaf->AABB->CollidingWithSphere(physicsNode.GetPosition(), physicsNode.GetBoundingRadius());
	}

	return false;
}
