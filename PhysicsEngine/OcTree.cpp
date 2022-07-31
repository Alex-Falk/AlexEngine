#include "OcTree.h"
#include <algorithm>

#include "PhysicsNode.h"
#include "PhysicsEngine.h"
#include "common.h"

namespace Physics
{
	OcTree::Node::Node()
	{
		PhysicsNodes.reserve(8);
	}

	vector<PhysicsNode*> OcTree::Node::GetAllPhysicsNodesInChildren()
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

	size_t OcTree::Node::GetNumberOfPhysicsNodes() const
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

	OcTree::OcTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax,
	               std::vector<PhysicsNode*> physicsNodes): WorldPartitioning()
	{
		OcTree(Vector3(xMin, yMin, zMin), Vector3(xMax, yMax, zMax), physicsNodes);
	}

	OcTree::OcTree(Vector3 min, Vector3 max, std::vector<PhysicsNode*> physicsNodes) : WorldPartitioning(),
		m_root(new Node())
	{
		m_root->AABB = new BoundingBox();
		m_root->AABB->ExpandToFit(min);
		m_root->AABB->ExpandToFit(max);
		m_root->Children = nullptr;

		m_physicsNodes = physicsNodes;

		if (m_physicsNodes.size() > OcTreeMaxNumber)
		{
			SplitNode(m_root, m_physicsNodes);
		}
	}

	OcTree::~OcTree()
	{
		TerminateTree(m_root);
	}

	void OcTree::TerminateTree(Node* node)
	{
		if (node)
		{
			if (node->Children)
			{
				for (int i = 0; i < 8; ++i)
				{
					if (node->Children[i]) { TerminateTree(node->Children[i]); }
				}
			}

			node->Children = nullptr;
			delete node;
			node = nullptr;
		}
	}

	void OcTree::SplitNode(Node* node, const vector<PhysicsNode*>& physicsNodesToAssign)
	{
		if (physicsNodesToAssign.size() > OcTreeMaxNumber)
		{
			BoundingBox** boxes = BoundingBox::SplitIntoEight(*node->AABB);

			node->Children = new Node*[8];
			for (int i = 8; i < 8; i++)
			{
				auto newNode = new Node();
				newNode->Children = nullptr;
				newNode->AABB = boxes[i];
				node->Children[i] = new Node();

				auto newPhysicsNodes = GetPhysicsNodes(newNode, physicsNodesToAssign);

				if (newPhysicsNodes.size() > OcTreeMaxNumber)
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

	void OcTree::AddPhysicsNode(PhysicsNode* physicsNode) const
	{
		TryAddPhysicsNode(m_root, physicsNode);
	}

	void OcTree::RemovePhysicsNode(PhysicsNode* physicsNode) const
	{
		TryRemovePhysicsNode(m_root, physicsNode);
	}

	vector<CollisionPair> OcTree::GetCollisionPairs() const
	{
		return CreateCollisionPairs(m_root);
	}

	std::vector<CollisionPair> OcTree::CreateCollisionPairs(Node* node)
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
						auto pairs = CreateCollisionPairs(node->Children[i]);
						collisionPairs.insert(collisionPairs.end(), pairs.begin(), pairs.end());
					}
				}
			}
			else if (node->PhysicsNodes.size() > 0)
			{
				for (size_t i = 0; i < node->PhysicsNodes.size() - 1; ++i)
				{
					for (size_t j = 0; j < node->PhysicsNodes.size(); ++j)
					{
						// TODO: Objects that shouldn't collide with each other?
						if (node->PhysicsNodes[i] == node->PhysicsNodes[j])
						{
							continue;
						}

						if (node->PhysicsNodes[i]->HasCollision() && node->PhysicsNodes[j]->HasCollision())
						{
							if (PhysicsEngine::PhysicsNodeSpheresOverlap(node->PhysicsNodes[i], node->PhysicsNodes[j]))
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

	std::vector<PhysicsNode*> OcTree::GetPhysicsNodes(const Node* node,
	                                                  const std::vector<PhysicsNode*>& elementsInParent)
	{
		std::vector<PhysicsNode*> newNodes;

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

	void OcTree::Update()
	{
		if (m_physicsNodes.empty()) return;

		for (auto& physicsNode : m_physicsNodes)
		{
			if (physicsNode->GetLinearVelocity().LengthSqr() > 0.f && !(std::find(
				m_movedNodes.begin(), m_movedNodes.end(), physicsNode) != m_movedNodes.end()))
			{
				m_movedNodes.push_back(physicsNode);
			}
		}

		UpdatePhysicsNodes();
		AdjustNodesPostUpdate();
	}

	void OcTree::UpdatePhysicsNodes()
	{
		CheckPhysicsNodesToUpdate(m_root);
	}

	void OcTree::AdjustNodesPostUpdate() const
	{
		CheckAdjustNode(m_root);
	}

	void OcTree::TryAddPhysicsNode(Node* node, PhysicsNode* physNode)
	{
		if (IsPhysicsNodeInNode(node, physNode))
		{
			if (node->Children)
			{
				for (size_t i = 0; i < 8; ++i)
				{
					TryAddPhysicsNode(node->Children[i], physNode);
				}
			}
			else
			{
				if (std::find(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physNode) == node->PhysicsNodes.
					end())
				{
					node->PhysicsNodes.push_back(physNode);
				}
			}
		}
	}

	void OcTree::TryRemovePhysicsNode(Node* node, PhysicsNode* physNode)
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
			node->PhysicsNodes.erase(std::remove(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physNode),
			                         node->PhysicsNodes.end());
		}
	}

	void OcTree::CheckPhysicsNodesToUpdate(Node* node)
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
					node->PhysicsNodes.erase(
						std::remove(node->PhysicsNodes.begin(), node->PhysicsNodes.end(), physicsNode),
						node->PhysicsNodes.end());
				}
				else if (itr == node->PhysicsNodes.end() && IsPhysicsNodeInNode(node, physicsNode))
				{
					node->PhysicsNodes.push_back(physicsNode);
				}
			}
		}

		m_movedNodes.clear();
	}

	void OcTree::CollapseNode(Node* node)
	{
	}

	void OcTree::CheckAdjustNode(Node* node)
	{
		if (node->Children && node->GetNumberOfPhysicsNodes() < OcTreeMaxNumber)
		{
			CollapseNode(node);
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				if (node->Children)
					CheckAdjustNode(node->Children[i]);
			}
		}
	}

	bool OcTree::IsPhysicsNodeInNode(Node* node, const PhysicsNode* physicsNode)
	{
		if (node && node->AABB)
		{
			return node->AABB->CollidingWithSphere(physicsNode->GetPosition(), physicsNode->GetBoundingRadius());
		}

		return false;
	}
}
