#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "../nclgl/mesh.h"


#ifndef HEIGHT_MAP_DEF_OFF
#define RAW_WIDTH 257
#define RAW_HEIGHT 257

#define HEIGHTMAP_X 16.0f
#define HEIGHTMAP_Z 16.0f
#define HEIGHTMAP_Y 1.25f
#define HEIGHTMAP_TEX_X 1.0f/16.0f
#define HEIGHTMAP_TEX_Z 1.0f/16.0f
#endif

class HeightMap : public Mesh
{
public:
	HeightMap(std::string name, uint16_t rawWidth = RAW_WIDTH, uint16_t rawHeight = RAW_HEIGHT,
	          float HeightMapX = HEIGHTMAP_X, float HeightMapY = HEIGHTMAP_Y, float HeightMapZ = HEIGHTMAP_Z,
	          float HeightMapTexX = HEIGHTMAP_TEX_X, float HeightMapTexZ = HEIGHTMAP_TEX_Z);

	~HeightMap(void) override
	{
	};
};
