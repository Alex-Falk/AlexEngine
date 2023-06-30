#include "HeightMap.h"

HeightMap::HeightMap(std::string name, const uint16_t rawWidth, const uint16_t rawHeight, const float HeightMapX,
                     const float HeightMapY, const float HeightMapZ, const float HeightMapTexX,
                     const float HeightMapTexZ)
{
	std::ifstream file(name.c_str(), ios::binary);
	if (!file)
	{
		return;
	}
	numVertices = rawWidth * rawHeight;
	numIndices = (rawWidth - 1) * (rawHeight - 1) * 6;
	vertices = new Vector3[numVertices];
	textureCoords = new Vector2F[numVertices];
	indices = new GLuint[numIndices];
	auto data = new unsigned char[numVertices];
	file.read((char*)data, numVertices * sizeof(unsigned char));
	file.close();

	for (uint16_t x = 0; x < rawWidth; ++x)
	{
		for (uint16_t z = 0; z < rawHeight; ++z)
		{
			uint16_t offset = (x * rawWidth) + z;

			vertices[offset] = Vector3(x * HeightMapX, data[offset] * HeightMapY, z * HeightMapZ);

			textureCoords[offset] = Vector2F(x * HeightMapTexX, z * HeightMapTexZ);
		}
	}
	delete data;
	numIndices = 0;

	for (uint16_t x = 0; x < rawWidth - 1; ++x)
	{
		for (uint16_t z = 0; z < rawHeight - 1; ++z)
		{
			uint16_t a = (x * (rawWidth)) + z;
			uint16_t b = ((x + 1) * (rawWidth)) + z;
			uint16_t c = ((x + 1) * (rawWidth)) + (z + 1);
			uint16_t d = (x * (rawWidth)) + (z + 1);

			indices[numIndices++] = c;
			indices[numIndices++] = b;
			indices[numIndices++] = a;

			indices[numIndices++] = a;
			indices[numIndices++] = d;
			indices[numIndices++] = c;
		}
	}
	GenerateNormals();
	GenerateTangents();

	BufferData();
}
