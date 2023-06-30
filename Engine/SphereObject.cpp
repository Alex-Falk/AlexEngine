#include "SphereObject.h"

#include "Common/CommonMeshes.h"
#include "Components/PhysicsComponent.h"
#include "Components/RenderComponent.h"

SphereObject::SphereObject(const Vector3& pos, float radius, bool dynamic, float mass, const Vector4& color) : GameObject()
{
	const auto renderComp = new RenderComponent(CommonMeshes::Sphere(), color);
	AddComponent(std::unique_ptr<Component>(renderComp));
	const auto physicsComp = new PhysicsComponent(pos, 1.f / mass, radius, dynamic, new Physics::SphereCollisionShape(radius));
	AddComponent(std::unique_ptr<Component>(physicsComp));

	physicsComp->GetWorldTransform().SetScalingVector({radius, radius, radius});
}
