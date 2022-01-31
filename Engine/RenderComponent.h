#pragma once

#include "Component.h"
#include <nclgl/RenderNode.h>

class RenderComponent :
    public Component, public RenderNode
{
    void OnInitialise() override;
};

