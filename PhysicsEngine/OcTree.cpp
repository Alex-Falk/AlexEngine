#include "OcTree.h"
#include <algorithm>

#include "PhysicsNode.h"
#include "PhysicsEngine.h"

Physics::OcTree::Node::Node()
{
	PhysicsNodes.reserve(8);
}

vector<Physics::PhysicsNode*> Physics::OcTree::Node::GetAllPhysicsNodesInChildren()
{
	if (!Children)
	{
		return PhysicsNodes;
	}

	vector<PhysicsNode*> physicsNodes;

	for (int i = 0; i < 8; ++i)
	{
		auto childrenNodes = Children[i]->GetAllPhysicsNodesInChildren();
		physicsNodes.insert(physicsNodes.end(), childrenNodes.begin(), childrenNodes.end());
	}

	return physicsNodes;
}

size_t Physics::OcTree::Node::GetNumberOfPhysicsNodes() const
{
	if (!Children)
	{
		return PhysicsNodes.size();
	}

	size_t totalNumber = PhysicsNodes.size();
	for (int i = 0; i < 8; ++i)
	{
		totalNumber += Children[i]->GetNumberOfPhysicsNodes();
	}

	return totalNumber;
}

Physics::OcTree::OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax,
                        std::vector<Physics::PhysicsNode*> physicsNodes)
{
	OcTree(Vector3(xMin, yMin, zMin), Vector3(xMax, yMax, zMax), physicsNodes);
}

Physics::OcTree::OcTree(Vector3 min, Vector3 max, std::vector<Physics::PhysicsNode*> physicsNodes) : m_root(new Node())
{
	m_root->AABB = new BoundingBox();
	m_root->AABB->ExpandToFit(min);
	m_root->AABB->ExpandToFit(max);
	m_root->Children = nullptr;

	m_physicsNodes = physicsNodes;

	if (m_physicsNodes.size() > Physics::OcTreeMaxNumber)
	{
		SplitNode(m_root, m_physicsNodes);
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

void Physics::OcTree::SplitNode(Node* node, vector<Physics::PhysicsNode*> physicsNodesToAssign)
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
	vector<CollisionPair> collisionPairs;

	if (node)
	{
		if (node->Children)
		{
			for (int i = 0; i < 8; ++i)
			{
				if (node->Children[i])
				{
					auto pairs = CreateCollisionPairsForNode(node->Children[i]);
					collisionPairs.insert(collisionPairs.end(), pairs.begin(), pairs.end());
				}
			}
		}
		else
		{
			for (size_t i = 0; i < node->PhysicsNodes.size() - 1; ++i)
			{
				for (size_t j = 0; i < node->PhysicsNodes.size(); ++j)
				{
					// TODO: Objects that shouldn't collide with each other?

					if (node->PhysicsNodes[i]->HasCollision() && node->PhysicsNodes[j]->HasCollision())
					{
						if (PhysicsNodeSpheresOverlap(node->PhysicsNodes[i],node->PhysicsNodes[j]))
						{
							collisionPairs.push_back({
								node->PhysicsNodes[i],
								node->PhysicsNodes[j]
								});
						}
					}
				}
			}
		}
	}
	return collisionPairs;
}

std::vector<Physics::PhysicsNode*> Physics::OcTree::GetPhysicsNodesInNode(const Node* node,
                                                                   const std::vector<Physics::PhysicsNode*>& elementsInParent)
{
	std::vector<Physics::PhysicsNode*> newNodes;

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



	if (m_physicsNodes.empty()) return;

	for(auto& physicsNode : m_physicsNodes)
	{
		if (physicsNode->GetLinearVelocity().LengthSqr() > 0.f && !(std::find(m_movedNodes.begin(), m_movedNodes.end(), m_physicsNodes) != m_movedNodes.end()))
		{
			m_movedNodes.push_back(physicsNode);
		}
	}
}

void Physics::OcTree::UpdatePhysicsNodes()
{
	CheckPhysicsNodesToUpdate(m_root);
}

void Physics::OcTree::AdjustNodesPostUpdate()
{
	CheckAdjustNode(m_root);
}

void Physics::OcTree::TryAddPhysicsNode(Node* node, PhysicsNode* physNode)
{
	if (IsPhysicsNodeInNode(node, physNode))
	{
		if (node->Children)
		{
			for(size_t i = 0; i < 8; ++i)
			{
				TryAddPhysicsNode(node->Children[i], physNode);
			}
		}
		else
		{
			node->PhysicsNodes.push_back(physNode);
		}
	}
}

void Physics::OcTree::TryRemovePhysicsNode(Node* node, PhysicsNode* physNode)
{
	if (node->Children)
	{
		for (size_t i = 0; i < 8; ++i)
		{
			TryAddPhysicsNode(node->Children[i], physNode);
		}
	}

	// TODO is this needed?
	if (std::find(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physNode) != node->PhysicsNodes.end())
	{
		node->PhysicsNodes.erase(std::remove(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physNode), node->PhysicsNodes.end());
	}
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
		for (auto& physicsNode : m_movedNodes)
		{
			auto itr = std::find(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physicsNode);
			if (itr != node->PhysicsNodes.end() && !IsPhysicsNodeInNode(node, physicsNode))
			{
				node->PhysicsNodes.erase(std::remove(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physicsNode), node->PhysicsNodes.end());
			}
			else if (itr == node->PhysicsNodes.end() && IsPhysicsNodeInNode(node, physicsNode))
			{
				node->PhysicsNodes.push_back(physicsNode);
			}
		}
	}

	m_movedNodes.clear();
}

void Physics::OcTree::CollapseNode(Node* node)
{

}

void Physics::OcTree::CheckAdjustNode(Node* node)
{
	if (node->Children && node->GetNumberOfPhysicsNodes() < OcTreeMaxNumber)
	{
		CollapseNode(node);
	}
	else
	{
		for (int i = 0; i < 8; ++i) {
			if (node->Children)
				CheckAdjustNode(node->Children[i]);
		}
	}
}

bool Physics::OcTree::IsPhysicsNodeInNode(Node* node, PhysicsNode* physicsNode)
{
	if (node && node->AABB)
	{
		return node->AABB->CollidingWithSphere(physicsNode->GetPosition(), physicsNode->GetBoundingRadius());
	}

	return false;
}
