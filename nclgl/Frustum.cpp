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
	auto xaxis = Vector3(mat[0][0], mat[1][0], mat[2][0]);
	auto yaxis = Vector3(mat[0][1], mat[1][1], mat[2][1]);
	auto zaxis = Vector3(mat[0][2], mat[1][2], mat[2][2]);
	auto waxis = Vector3(mat[0][3], mat[1][3], mat[2][3]);
	// RIGHT
	planes[0] = Plane(waxis - xaxis, (mat[3][3] - mat[3][0]), true);
	// LEFT
	planes[1] = Plane(waxis + xaxis, (mat[3][3] + mat[3][0]), true);
	// BOTTOM
	planes[2] = Plane(waxis + yaxis, (mat[3][3] + mat[3][1]), true);
	// TOP
	planes[3] = Plane(waxis - yaxis, (mat[3][3] - mat[3][1]), true);
	// FAR
	planes[4] = Plane(waxis - zaxis, (mat[3][3] - mat[3][2]), true);
	// NEAR
	planes[5] = Plane(waxis + zaxis, (mat[3][3] + mat[3][2]), true);
}
