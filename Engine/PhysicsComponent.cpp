#include "PhysicsComponent.h"

#include "GameObject.h"
#include "PhysicsEngine/PhysicsEngine.h"

void PhysicsComponent::OnInitialise()
{
	PhysicsEngine::Instance()->AddPhysicsObject(this);

	SetOnUpdateCallback([capture0 = GetOwner()](auto&& ph1)
	{
		capture0->SetTransform(std::forward<decltype(ph1)>(ph1));
	});
}

void PhysicsComponent::OnUpdate(float dt)
{
}
