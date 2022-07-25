#pragma once

#include "Component.h"
#include <nclgl/RenderNode.h>

class RenderComponent :
    public Component, public RenderNode
{
public:
	RenderComponent(Mesh* m = nullptr, const Vector4& colour = Vector4(1, 1, 1, 1))
		: Component("RenderComponent"), RenderNode(m, colour)
	{
	}

    void OnInitialise() override;

    void OnUpdate(float dt) override;
};

