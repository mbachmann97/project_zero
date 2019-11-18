#include "mesh.h"
#include <iostream>

Mesh::Mesh(MeshSize _size, Position _startPos) {
	this->size = _size;
	this->startPos = _startPos;
	this->endPos = Position{ _startPos.x + _size.sizeX, _startPos.y + _size.sizeY, _startPos.z - _size.sizeZ };
	this->drawPos = this->startPos;
	this->numVertices = (size.sizeX * size.sizeY * size.sizeZ) * 36;
	this->tempMeshVertNum = 0;
	this->vertices = new Vertex[this->numVertices];
	this->tempBlockFaces = new BlockFace[6];
	Block block;
}

Mesh::~Mesh() {
	//delete &block;
}

void Mesh::GenerateMesh() {
	for (int z = 1; z <= size.sizeZ; z++) {
		for (int y = 1; y <= size.sizeY; y++) {
			for (int x = 1; x <= size.sizeX; x++) {
				block.CreateNewBlock(Position{ drawPos.x, drawPos.y, drawPos.z }, 1, 4.0f, 1.0f);
				tempBlockFaces = block.GetFaces();

				for (int i = 0; i < 6; i++) {
					//float32 x = tempBlockVertices[i].x; float32 y = tempBlockVertices[i].y; float32 z = tempBlockVertices[i].z;
					//float32 ex = endPos.x; float32 ey = endPos.y; float32 ez = endPos.z;
					//float32 sx = startPos.x; float32 sy = startPos.y; float32 sz = startPos.z;

					if (IsFaceValid(tempBlockFaces[i])) {
						vertices[tempMeshVertNum] = tempBlockFaces[i].left.a;
						tempMeshVertNum++;
						vertices[tempMeshVertNum] = tempBlockFaces[i].left.b;
						tempMeshVertNum++;
						vertices[tempMeshVertNum] = tempBlockFaces[i].left.c;
						tempMeshVertNum++;
						vertices[tempMeshVertNum] = tempBlockFaces[i].right.a;
						tempMeshVertNum++;
						vertices[tempMeshVertNum] = tempBlockFaces[i].right.b;
						tempMeshVertNum++;
						vertices[tempMeshVertNum] = tempBlockFaces[i].right.c;
						tempMeshVertNum++;
					}
				}

				drawPos.x += blockScale;
			}
			drawPos.y += blockScale;
			drawPos.x = startPos.x;
		}
		drawPos.z -= blockScale;
		drawPos.x = startPos.x;
		drawPos.y = startPos.y;
	}
}

bool Mesh::IsFaceValid(BlockFace face) {
	if (face.left.a.x == startPos.x && face.left.b.x == startPos.x && face.left.c.x == startPos.x && face.right.a.x == startPos.x && face.right.b.x == startPos.x && face.right.c.x == startPos.x) {
		return true;
	}
	if (face.left.a.x == endPos.x && face.left.b.x == endPos.x && face.left.c.x == endPos.x && face.right.a.x == endPos.x && face.right.b.x == endPos.x && face.right.c.x == endPos.x) {
		return true;
	}

	if (face.left.a.y == startPos.y && face.left.b.y == startPos.y && face.left.c.y == startPos.y && face.right.a.y == startPos.y && face.right.b.y == startPos.y && face.right.c.y == startPos.y) {
		return true;
	}
	if (face.left.a.y == endPos.y && face.left.b.y == endPos.y && face.left.c.y == endPos.y && face.right.a.y == endPos.y && face.right.b.y == endPos.y && face.right.c.y == endPos.y) {
		return true;
	}

	if (face.left.a.z == startPos.z && face.left.b.z == startPos.z && face.left.c.z == startPos.z && face.right.a.z == startPos.z && face.right.b.z == startPos.z && face.right.c.z == startPos.z) {
		return true;
	}
	if (face.left.a.z == endPos.z && face.left.b.z == endPos.z && face.left.c.z == endPos.z && face.right.a.z == endPos.z && face.right.b.z == endPos.z && face.right.c.z == endPos.z) {
		return true;
	}
	else {
		return false;
	}
}

Vertex* Mesh::GetMesh() {
	return vertices;
}

uint32 Mesh::GetNumVertices() {
	return tempMeshVertNum;
}