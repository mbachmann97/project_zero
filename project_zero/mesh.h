#pragma once

#include "defines.h"
#include "block.h"

class Mesh {
public:
	Mesh(MeshSize _size, Position _startPos);
	~Mesh();

	void GenerateMesh();
	Vertex* GetMesh();
	uint32 GetNumVertices();
	
private:
	bool IsFaceValid(BlockFace face);

	Block block;
	MeshSize size;
	Position drawPos;
	Position startPos;
	Position endPos;
	uint32 numVertices;
	uint32 tempMeshVertNum;
	Vertex* vertices;
	BlockFace* tempBlockFaces;
	const float32 blockScale = 1.0f;
};
