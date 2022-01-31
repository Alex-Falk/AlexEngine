#include "RenderComponent.h"
#include <PhysicsEngine\GraphicsPipeline.h>

void RenderComponent::OnInitialise()
{
	GraphicsPipeline::Instance()->AddRenderNode(this);
}
