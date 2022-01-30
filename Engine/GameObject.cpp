#include "GameObject.h"
#include "PhysicsEngine/GraphicsPipeline.h"

GameObject::GameObject()
{
}

GameObject::GameObject(RenderNode* renderNode, PhysicsObject* physicsObject)
{
	m_renderNode = renderNode;
	m_physicsObject = physicsObject;

	GraphicsPipeline::Instance()->AddRenderNode(renderNode);
}

GameObject::~GameObject()
{
}

UUID GameObject::GetId()
{
	return m_id;
}