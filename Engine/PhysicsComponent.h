#pragma once
#include "Component.h"
#include <PhysicsEngine/PhysicsNode.h>

class PhysicsComponent :
    public Component, public PhysicsNode
{
public:
    PhysicsComponent() {}

private:
    void OnInitialise() override;

    void OnUpdate(float dt) override;
};

