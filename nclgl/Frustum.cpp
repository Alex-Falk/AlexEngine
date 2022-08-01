#include "Frustum.h"

bool Frustum::InsideFrustum(RenderNode& n)
{
	for (int p = 0; p < 6; ++p)
	{
		if (!planes[p].SphereInPlane(n.GetWorldTransform().GetPositionVector(), n.GetBoundingRadius()))
		{
			return false; // RenderNode is outside this plane !
		}
	}
	return true; // RenderNode is inside every plane ...
}

void Frustum::FromMatrix(const Maths::Matrix4& mat)
{
	auto xaxis = Vector3(mat[0], mat[4], mat[8]);
	auto yaxis = Vector3(mat[1], mat[5], mat[9]);
	auto zaxis = Vector3(mat[2], mat[6], mat[10]);
	auto waxis = Vector3(mat[3], mat[7], mat[11]);
	// RIGHT
	planes[0] = Plane(waxis - xaxis, (mat[15] - mat[12]), true);
	// LEFT
	planes[1] = Plane(waxis + xaxis, (mat[15] + mat[12]), true);
	// BOTTOM
	planes[2] = Plane(waxis + yaxis, (mat[15] + mat[13]), true);
	// TOP
	planes[3] = Plane(waxis - yaxis, (mat[15] - mat[13]), true);
	// FAR
	planes[4] = Plane(waxis - zaxis, (mat[15] - mat[14]), true);
	// NEAR
	planes[5] = Plane(waxis + zaxis, (mat[15] + mat[14]), true);
}
