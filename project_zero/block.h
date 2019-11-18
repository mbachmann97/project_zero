#pragma once

#include "defines.h"
#include <vector>

class Block {
public:
	Block();

	void CreateNewBlock(Position startVertex, int16 blockType, float32 texturesPerRow, float32 texturesPerColumn);
	BlockFace* GetFaces();
private:
	void CalcVertices();
	void GetUvFromBlockType();
	Position start;
	UV textureSide;
	UV textureTop;
	UV textureBottom;
	int16 type;
	float32 texStepX;
	float32 texStepY;
	BlockFace* faces;
	const int16 numVertices = 36;
	Vertex* tempVertices;
	const float32 scale = 1.0f;
};
