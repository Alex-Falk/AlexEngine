#pragma once
#include "nclgl/BoundingBox.h"

namespace Physics
{
	class Node;

	class kDTree
	{
		struct Node
		{
			Node* Parent = nullptr;
			Node** Children;

			BoundingBox* AABB;
		};

		Node* root = nullptr;

		kDTree(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax, std::vector<Physics::Node*>* physicsNodes);
		KDTree(Vector3 min, Vector3 max, std::vector<Physics::Node*>* physicsNodes);
		~kDTree();

		void TerminateTree(Node** node);


	};
}
