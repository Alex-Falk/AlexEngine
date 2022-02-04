#pragma once
#include "Component.h"
#include <PhysicsEngine/Node.h>

class PhysicsComponent :
    public Component, public Physics::Node
{
public:
    PhysicsComponent() {}

private:
    void OnInitialise() override;

    void OnUpdate(float dt) override;
};

