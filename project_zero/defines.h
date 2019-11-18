#pragma once
#include <cstdint>
#include <filesystem>

namespace fs = std::experimental::filesystem;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;

typedef size_t size;

struct Vertex {
	float32 x;
	float32 y;
	float32 z;

	float32 u;
	float32 v;

	float32 nx;
	float32 ny;
	float32 nz;
};

struct Position {
	float32 x;
	float32 y;
	float32 z;
};

struct UV {
	float32 u;
	float32 v;
};

struct MeshSize {
	int32 sizeX;
	int32 sizeY;
	int32 sizeZ;
};

struct Triangle {
	Vertex a;
	Vertex b;
	Vertex c;
};

struct BlockFace {
	Triangle left;
	Triangle right;
};

struct MapFile {
	fs::path path;
	Position startPos = Position{ 0 };
};