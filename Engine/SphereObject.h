#pragma once
#include "GameObject.h"
class SphereObject : public GameObject
{
public:
	SphereObject(const Vector3& pos, float radius, bool dynamic, float mass, const Vector4& color);

};

