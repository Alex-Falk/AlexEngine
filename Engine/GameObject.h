#pragma once

#include <rpc.h>

#include "nclgl/RenderNode.h"
#include "PhysicsEngine/PhysicsObject.h"

class GameObject {

public:
	GameObject();
	GameObject(RenderNode* renderNode, PhysicsObject* physicsObject);
	~GameObject();

	UUID GetId();

protected:

private:

	UUID m_id;

	RenderNode* m_renderNode;
	PhysicsObject* m_physicsObject;
};
