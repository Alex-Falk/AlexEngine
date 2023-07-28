#include "RenderComponent.h"
#include <nclgl/GraphicsPipeline.h>
#include <Engine/GameObject.h>

void RenderComponent::OnInitialise()
{
	GraphicsPipeline::Instance()->AddRenderNode(this);
}

void RenderComponent::OnUpdate(float dt)
{
	SetTransform(GetOwner()->GetTransform());

	Update(dt);
}
