#pragma once
#include "Component.h"
#include <PhysicsEngine/PhysicsNode.h>

class PhysicsComponent :
    public Component, public Physics::PhysicsNode
{
public:
	PhysicsComponent(const Vector3& initialPos, float inverseMass, float boundingRadius, bool applyGravity)
		: PhysicsNode(initialPos, inverseMass, boundingRadius, applyGravity)
	{
	}

private:
    void OnInitialise() override;

    void OnUpdate(float dt) override;
};

