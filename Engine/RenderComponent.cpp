#include "RenderComponent.h"
#include <nclgl\GraphicsPipeline.h>

void RenderComponent::OnInitialise()
{
	GraphicsPipeline::Instance()->AddRenderNode(this);
}
