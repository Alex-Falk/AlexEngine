#include "GridSystem.h"

template<uint16_t x, uint16_t z>
GridSystem<x, z>::GridSystem(float boxSize)
{
	m_boxSize = boxSize;

	for (auto i = 0; i < x; ++i)
	{
		for (auto j = 0; j < z; ++j)
		{
			m_grid[i][j] = new GridPoint();
			m_grid[i][j]->color = Vector4(Math::Rand(0.f, 1.f), Math::Rand(0.f, 1.f), Math::Rand(0.f, 1.f), 1.f);
		}
	}
}

template<uint16_t x, uint16_t z>
GridPoint* GridSystem<x, z>::GetClosestGridPoint(const Vector3& worldPos)
{
	Vector3 diff = worldPos - m_originPos;
	int xIndex = round(diff.x / (m_boxSize * x));
	int zIndex = round(diff.z / (m_boxSize * z));

	return m_grid[xIndex][zIndex];
}

template<uint16_t x, uint16_t z>
Vector3 GridSystem<x, z>::GetPositionOfGridPoint(uint16_t x, uint16_t z)
{
	return m_originPos + Vector3( x * m_boxSize, 0.f, z * m_boxSize);
}

