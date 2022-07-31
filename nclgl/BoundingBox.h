/******************************************************************************
Class: BoundingBox
Implements:
Author:
Pieran Marris <p.marris@newcastle.ac.uk>
Description:
A very basic way of representing an Axis Algined Bounding Box (AABB), that represents a
bounding cuboid that encompasses a set of given points. The box is always orientated in the same
way, such that the x,y,z of the maximum/minimum dimensions are always algined with the x,y,z axes of the world.

This is currently used to help assist with the shadow mapping, though could be extended to help assist
with graphics frustum culling by using both AABB and bounding sphere's inside SceneNode/Object.

*/ /////////////////////////////////////////////////////////////////////////////

#pragma once
#include <Maths/Vector3.h>
#include <Maths/Vector4.h>
#include <nclgl/common.h>
#include <nclgl/NCLDebug.h>

struct BoundingBox
{
	Vector3 _min;
	Vector3 _max;


	//Initialize _min to max possible value and vice versa to force the first value incorporated to always be used for both min and max points.
	BoundingBox()
		: _min(FLT_MAX, FLT_MAX, FLT_MAX)
		  , _max(-FLT_MAX, -FLT_MAX, -FLT_MAX)
	{
	}

	//Expand the boundingbox to fit a given point. 
	//  If no points have been set yet, both _min and _max will equal the point provided.
	void ExpandToFit(const Vector3& point)
	{
		_min.x = min(_min.x, point.x);
		_min.y = min(_min.y, point.y);
		_min.z = min(_min.z, point.z);
		_max.x = max(_max.x, point.x);
		_max.y = max(_max.y, point.y);
		_max.z = max(_max.z, point.z);
	}

	Vector3 GetHalfSize() const
	{
		return _max - GetPosition();
	}

	Vector3 GetPosition() const
	{
		return (_max + _min) / 2.f;
	}


	//Transform the given AABB (Axis Aligned Bounding Box) and returns a new AABB that encapsulates the new rotated bounding box.
	BoundingBox Transform(const Maths::Matrix4& mtx)
	{
		BoundingBox bb;
		bb.ExpandToFit(mtx * Vector3(_min.x, _min.y, _min.z));
		bb.ExpandToFit(mtx * Vector3(_max.x, _min.y, _min.z));
		bb.ExpandToFit(mtx * Vector3(_min.x, _max.y, _min.z));
		bb.ExpandToFit(mtx * Vector3(_max.x, _max.y, _min.z));

		bb.ExpandToFit(mtx * Vector3(_min.x, _min.y, _max.z));
		bb.ExpandToFit(mtx * Vector3(_max.x, _min.y, _max.z));
		bb.ExpandToFit(mtx * Vector3(_min.x, _max.y, _max.z));
		bb.ExpandToFit(mtx * Vector3(_max.x, _max.y, _max.z));
		return bb;
	}

	void DebugDraw() const
	{
		float x1 = _min.x;
		float y1 = _min.y;
		float z1 = _min.z;

		float x2 = _max.x;
		float y2 = _max.y;
		float z2 = _max.z;

		Vector3 v[8];

		v[0] = Vector3(x1, y1, z1);
		v[1] = Vector3(x1, y2, z1);
		v[2] = Vector3(x1, y1, z2);
		v[3] = Vector3(x1, y2, z2);
		v[4] = Vector3(x2, y1, z1);
		v[5] = Vector3(x2, y2, z1);
		v[6] = Vector3(x2, y1, z2);
		v[7] = Vector3(x2, y2, z2);

		NCLDebug::DrawThickLine(v[0], v[1], 0.05f, Vector4(1, 0, 0, 0.2f));
		NCLDebug::DrawThickLine(v[0], v[2], 0.05f, Vector4(1, 0, 0, 0.2f));
		NCLDebug::DrawThickLine(v[0], v[4], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[1], v[3], 0.05f, Vector4(1, 0, 0, 0.2f));
		NCLDebug::DrawThickLine(v[1], v[5], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[2], v[3], 0.05f, Vector4(1, 0, 0, 0.2f));
		NCLDebug::DrawThickLine(v[2], v[6], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[3], v[7], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[4], v[5], 0.05f, Vector4(1, 0, 0, 0.2f));
		NCLDebug::DrawThickLine(v[4], v[6], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[5], v[7], 0.05f, Vector4(1, 0, 0, 0.2f));

		NCLDebug::DrawThickLine(v[6], v[7], 0.05f, Vector4(1, 0, 0, 0.2f));
	}

	bool CollidingWithSphere(Vector3 p, float r)
	{
		Vector3 closestPt;

		if (p.x < _min.x) { closestPt.x = _min.x; }
		else if (p.x > _max.x) { closestPt.x = _max.x; }
		else { closestPt.x = p.x; }

		if (p.y < _min.y) { closestPt.y = _min.y; }
		else if (p.y > _max.y) { closestPt.y = _max.y; }
		else { closestPt.y = p.y; }

		if (p.z < _min.z) { closestPt.z = _min.z; }
		else if (p.z > _max.z) { closestPt.z = _max.z; }
		else { closestPt.z = p.z; }

		Vector3 diff = p - closestPt;
		float dsq = diff.LengthSqr();

		return dsq < r * r;
	}

	bool CollidingWithBoundingBox(const BoundingBox& other) const
	{
		const Vector3 delta = GetPosition() - other.GetPosition();
		const Vector3 totalSize = GetHalfSize() + other.GetHalfSize();

		return abs(delta.x) < totalSize.x &&
			abs(delta.y) < totalSize.y &&
			abs(delta.z) < totalSize.z;
	}

	static BoundingBox** SplitIntoEight(const BoundingBox& bb)
	{
		// BOTTOM
		//	b3 --- b34 --- b4
		//	|	    | 	   |
		//	b13--- bm --- b24	
		//	|	    | 	   |
		//	min --- b12 --- b2
		//
		// TOP
		//	t3 --- t34 --- t4
		//	|	    | 	   |
		//	t13--- mt --- t23	
		//	|	    | 	   |
		//	t1 --- t12 --- t2
		//	
		// Middle
		//	m3 --- m34 --- m4
		//	|	    | 	   |
		//	m13 --- mm --- m24	
		//	|	    | 	   |
		//	m1 --- m12 --- m2

		// min-mm, b12-m24, b13-m34, bm-m4, m1-mt, m12-t23, m13-t34, mm-max

		const auto boxes = new BoundingBox*[8];

		const Vector3 min = bb._min;
		const Vector3 max = bb._max;
		const Vector3 mm = (min + max) * .5f;

		Vector3 dims[16]
		{
			min,
			mm,
			Vector3(mm.x, min.y, min.z),
			Vector3(max.x, mm.y, mm.z),
			Vector3(min.x, min.y, mm.z),
			Vector3(mm.x, min.y, max.z),
			Vector3(mm.x, min.y, mm.z),
			Vector3(max.x, mm.y, max.z),
			Vector3(min.x, mm.y, min.z),
			Vector3(mm.x, max.y, mm.z),
			Vector3(mm.x, mm.y, min.z),
			Vector3(max.x, max.y, mm.z),
			Vector3(min.x, mm.y, mm.z),
			Vector3(mm.x, max.y, max.z),
			mm,
			max
		};

		for (ptrdiff_t i = 0; i < 8; i++)
		{
			const auto box = new BoundingBox();
			box->ExpandToFit(dims[i * 2]);
			box->ExpandToFit(dims[i * 2 + 1]);
			boxes[i] = box;
		}

		return boxes;
	}
};
