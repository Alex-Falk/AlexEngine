#pragma once
#include <Maths/Vector4.h>

struct GridPoint {
	Vector4 color;
};

template<uint16_t x, uint16_t z>
class GridSystem
{
public:
	GridSystem(float boxSize);

	GridPoint* GetClosestGridPoint(const Vector3& worldPos);

	Vector3 GetPositionOfGridPoint(uint16_t x, uint16_t z);

private:

	GridPoint* m_grid[x][z];
	float m_boxSize;
	Vector3 m_originPos;
};

