#include "PhysicsComponent.h"

#include "GameObject.h"
#include "PhysicsEngine/PhysicsEngine.h"

PhysicsComponent::PhysicsComponent(const Vector3& initialPos, float inverseMass, float boundingRadius, bool applyGravity, Physics::CollisionShape* collisionShape)
	: Component("PhysicsComponent"), PhysicsNode(initialPos, inverseMass, boundingRadius, applyGravity)
{
	if (collisionShape)
		this->SetCollisionShape(collisionShape);
}

void PhysicsComponent::OnInitialise()
{
	Physics::PhysicsEngine::Instance()->AddPhysicsObject(this);

	SetOnUpdateCallback([capture0 = GetOwner()](auto&& ph1)
	{
		capture0->SetTransform(std::forward<decltype(ph1)>(ph1));
	});
}

void PhysicsComponent::OnUpdate(float dt)
{
}
