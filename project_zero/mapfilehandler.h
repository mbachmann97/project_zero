#pragma once

#include "defines.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>

#include <filesystem>
namespace fs = std::experimental::filesystem;

class MapFileHandler {
public:
	MapFileHandler();

	void WriteToFile(Vertex* vd1, Vertex* vd2, Vertex* vd3, Vertex* vd4, uint64 numVertices);
	void CalcMesh();
	std::vector<Vertex> GetV1();
	std::vector<Vertex> GetV2();
	std::vector<Vertex> GetV3();
	std::vector<Vertex> GetV4();
	uint64 GetNumVertices();

private:
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices2;
	std::vector<Vertex> vertices3;
	std::vector<Vertex> vertices4;
	std::vector<MapFile> mapFiles;
	uint64 numVertices;
	Position startVertex;
};
