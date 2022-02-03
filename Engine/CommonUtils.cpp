#include "CommonUtils.h"
#include "CommonMeshes.h"
#include <nclgl\RenderNode.h>
#include <functional>

#include <Engine/RenderComponent.h>
#include <Engine/PhysicsComponent.h>

#include "PhysicsEngine/CollisionShape.h"
#include "nclgl/ScreenPicker.h"

//Horrible!!!
// TODO: Fix these variables!
bool dragDataSet = false;
Matrix3 dragDataInertia;
float dragDataMass;

Vector4 CommonUtils::GenColor(float scalar, float alpha)
{
	Vector4 c;
	c.w = alpha;

	//Hue
	float t;
	c.x = abs(modf(scalar + 1.0f, &t) * 6.0f - 3.0f) - 1.0f;
	c.y = abs(modf(scalar + 2.0f / 3.0f, &t) * 6.0f - 3.0f) - 1.0f;
	c.z = abs(modf(scalar + 1.0f / 3.0f, &t) * 6.0f - 3.0f) - 1.0f;

	//Safety Checks
	c.x = min(max(c.x, 0.0f), 1.0f);
	c.y = min(max(c.y, 0.0f), 1.0f);
	c.z = min(max(c.z, 0.0f), 1.0f);

	return c;
}

Vector4 CommonUtils::GenHSVColor(const Vector3& hsv, float alpha)
{
	Vector4 c = GenColor(hsv.x, alpha);

	//Saturation & Value
	c.x = hsv.z * (c.x * hsv.y + 1.0f - hsv.y);
	c.y = hsv.z * (c.y * hsv.y + 1.0f - hsv.y);
	c.z = hsv.z * (c.z * hsv.y + 1.0f - hsv.y);

	return c;
}

GameObject* CommonUtils::BuildSphereObject(
	const std::string& name,
	const Vector3& pos,
	float radius,
	bool physics_enabled,
	bool apply_gravity,
	float inverse_mass,
	bool collidable,
	bool dragable,
	const Vector4& color)
{
	//Due to the way SceneNode/RenderNode's were setup, we have to make a dummy node which has the mesh and scaling transform
	// and a parent node that will contain the world transform/physics transform
	RenderComponent* rnode = new RenderComponent();

	RenderNode* dummy = new RenderNode(CommonMeshes::Sphere(), color);
	dummy->SetTransform(Matrix4::Scale(Vector3(radius, radius, radius)));

	//dummy->SetMaterial(GraphicsPipeline::Instance()->GetAllMaterials()[matType]);
	dummy->SetBoundingRadius(radius);
	rnode->AddChild(dummy);

	rnode->SetTransform(Matrix4::Translation(pos));
	rnode->SetBoundingRadius(radius);

	PhysicsComponent* pnode = NULL;	
	if (physics_enabled)
	{
		pnode = new PhysicsComponent();
		pnode->SetPosition(pos);
		pnode->SetInverseMass(inverse_mass);
		pnode->SetGravityEnabled(apply_gravity);
		//pnode->SetBoundingRadius(radius);
		//pnode->SetType(objectType);

		if (!collidable)
		{
			//Even without a collision shape, the inertia matrix for rotation has to be derived from the objects shape
			//pnode->SetInverseInertia(SphereCollisionShape(radius).BuildInverseInertia(inverse_mass));
		}
		else
		{
			//CollisionShape* pColshape = new SphereCollisionShape(radius);
			//pnode->SetCollisionShape(pColshape);
			//pnode->SetInverseInertia(pColshape->BuildInverseInertia(inverse_mass));
		}
	}

	GameObject* obj = new GameObject();
	obj->AddComponent(rnode);
	obj->AddComponent(pnode);


	if (dragable)
	{
		ScreenPicker::Instance()->RegisterNodeForMouseCallback(
			dummy
		);
	}

	return obj;
}

GameObject* CommonUtils::BuildCuboidObject(
	const std::string& name,
	const Vector3& pos,
	const Vector3& halfdims,
	bool physics_enabled,
	bool apply_gravity,
	float inverse_mass,
	bool collidable,
	bool dragable,
	//PhysNodeType objectType,
	const Vector4& color)
	//MATERIALTYPE matType)
{
	//Due to the way SceneNode/RenderNode's were setup, we have to make a dummy node which has the mesh and scaling transform
	// and a parent node that will contain the world transform/physics transform
	RenderComponent* rnode = new RenderComponent();

	Mesh * mesh = new Mesh();
	*mesh = *CommonMeshes::Cube();
	//if (tex) { mesh->SetTexture(tex); }

	RenderNode* dummy = new RenderNode(mesh, color);
	
	dummy->SetTransform(Matrix4::Scale(halfdims));

	//dummy->SetMaterial(GraphicsPipeline::Instance()->GetAllMaterials()[matType]);
	dummy->SetBoundingRadius(halfdims.Length());

	rnode->AddChild(dummy);
	
	rnode->SetTransform(Matrix4::Translation(pos));
	rnode->SetBoundingRadius(halfdims.Length());

	PhysicsComponent* pnode = NULL;
	if (physics_enabled)
	{
		pnode = new PhysicsComponent();
		pnode->SetPosition(pos);
		pnode->SetInverseMass(inverse_mass);
		pnode->SetGravityEnabled(apply_gravity);
		//pnode->SetType(objectType);

		float x = halfdims.x*2.0f;
		float y = halfdims.y*2.0f;
		float z = halfdims.z*2.0f;
		float a;
		if (x >= y && x >= z) { a = x; }
		else if (y > x && y >= z) { a = y; }
		else { a = z; }

		//pnode->SetBoundingRadius(a * sqrt(3.0f) / 2.0f);

		if (!collidable)
		{
			//Even without a collision shape, the inertia matrix for rotation has to be derived from the objects shape
			//pnode->SetInverseInertia(CuboidCollisionShape(halfdims).BuildInverseInertia(inverse_mass));
		}
		else
		{
			//CollisionShape* pColshape = new CuboidCollisionShape(halfdims);
			//pnode->SetCollisionShape(pColshape);
			//pnode->SetInverseInertia(pColshape->BuildInverseInertia(inverse_mass));
		}
	}

	GameObject* obj = new GameObject();
	obj->AddComponent(rnode);
	obj->AddComponent(pnode);

	if (dragable)
	{
		ScreenPicker::Instance()->RegisterNodeForMouseCallback(
			dummy
		);
	}
	
	return obj;
}

GameObject* CommonUtils::BuildPlaneObject(
	const std::string& name,
	const Vector3& pos,
	const Vector3& halfdims,
	bool physics_enabled,
	bool apply_gravity,
	float inverse_mass,
	bool collidable,
	bool dragable,
	const Vector4& color)
{
	//Due to the way SceneNode/RenderNode's were setup, we have to make a dummy node which has the mesh and scaling transform
	// and a parent node that will contain the world transform/physics transform
	RenderComponent* rnode = new RenderComponent();

	RenderNode* dummy = new RenderNode(Mesh::GenerateQuad(), color);
	dummy->SetTransform(Matrix4::Scale(halfdims));

	//dummy->SetMaterial(GraphicsPipeline::Instance()->GetAllMaterials()[matType]);
	dummy->SetBoundingRadius(halfdims.Length());

	rnode->AddChild(dummy);

	rnode->SetTransform(Matrix4::Translation(pos));
	rnode->SetBoundingRadius(halfdims.Length());

	PhysicsComponent* pnode = NULL;
	if (physics_enabled)
	{
		pnode = new PhysicsComponent();
		pnode->SetPosition(pos);
		pnode->SetInverseMass(inverse_mass);
		//pnode->SetType(objectType);

		float x = halfdims.x*2.0f;
		float y = halfdims.y*2.0f;
		float z = halfdims.z*2.0f;
		float a;
		if (x >= y && x >= z) { a = x; }
		else if (y > x && y >= z) { a = y; }
		else { a = z; }

		//pnode->SetBoundingRadius(a * sqrt(3.0f) / 2.0f);

		if (!collidable)
		{
			//Even without a collision shape, the inertia matrix for rotation has to be derived from the objects shape
			//pnode->SetInverseInertia(CuboidCollisionShape(halfdims).BuildInverseInertia(inverse_mass));
		}
		else
		{
			//CollisionShape* pColshape = new CuboidCollisionShape(halfdims);
			//pnode->SetCollisionShape(pColshape);
			//pnode->SetInverseInertia(pColshape->BuildInverseInertia(inverse_mass));
		}
	}

	GameObject* obj = new GameObject();
	obj->AddComponent(rnode);
	obj->AddComponent(pnode);

	if (dragable)
	{
		ScreenPicker::Instance()->RegisterNodeForMouseCallback(
			dummy
		);
	}

	return obj;
}

GameObject* CommonUtils::InvisibleWall(
	const std::string& name,
	const Vector3& pos,
	const Vector3& halfdims)
{
	PhysicsComponent* pnode = NULL;

	pnode = new PhysicsComponent();
	//pnode->SetPosition(pos);
	//pnode->SetInverseMass(0);
	//pnode->SetType(INVISIBLE_WALL);

	float x = halfdims.x*2.0f;
	float y = halfdims.y*2.0f;
	float z = halfdims.z*2.0f;
	float a;
	if (x >= y && x >= z) { a = x; }
	else if (y > x && y >= z) { a = y; }
	else { a = z; }

	//pnode->SetBoundingRadius(a * sqrt(3.0f) / 2.0f);


	//CollisionShape* pColshape = new CuboidCollisionShape(halfdims);
	//pnode->SetCollisionShape(pColshape);
	//pnode->SetInverseInertia(pColshape->BuildInverseInertia(0));

	RenderComponent* rnode = new RenderComponent();
	GameObject* obj = new GameObject();
	obj->AddComponent(rnode);
	obj->AddComponent(pnode);

	return obj;
}