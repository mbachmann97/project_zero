#include "mapfilehandler.h"

MapFileHandler::MapFileHandler() {
	this->name = "pj.mapfile";
}

void MapFileHandler::WriteToFile(Vertex* vd1, Vertex* vd2, Vertex* vd3, Vertex* vd4, uint64 _numVertices) {

	std::string sFilename = "^" + std::to_string(vd1[0].x) + "_" + std::to_string(vd1[0].y) + "_" + std::to_string(vd1[0].z) + "$.mapfile";
	fs::path filename = sFilename;
	fs::path path = fs::current_path();
	fs::path dirPath = path;
	dirPath /= "mapdata";
	path /= "mapdata/" / filename;
	MapFile testFile;
	testFile.path = path;
	testFile.startPos = Position{ vd1[0].x, vd1[0].y, vd1[0].z };
	//std::cout << path << std::endl;

	std::string tempPath;
	for (const auto& entry : fs::directory_iterator(dirPath)) {
		MapFile tempMapFile;
		tempMapFile.path = entry.path();
		tempPath = entry.path().string();
		tempPath = tempPath.erase(0, tempPath.find("^"));
		tempPath = tempPath.erase(0, 1);
		std::string xPos = tempPath.substr(0, tempPath.find("_"));
		tempPath = tempPath.erase(0, xPos.length() + 1);
		std::string yPos = tempPath.substr(0, tempPath.find("_"));
		tempPath = tempPath.erase(0, yPos.length() + 1);
		std::string zPos = tempPath.substr(0, tempPath.find("$"));
		tempMapFile.startPos = Position{ std::stof(xPos.c_str()), std::stof(yPos.c_str()), std::stof(zPos.c_str()) };
		std::cout << tempMapFile.path << " " << tempMapFile.startPos.x << " " << tempMapFile.startPos.y << " " << tempMapFile.startPos.z << std::endl;
		mapFiles.push_back(tempMapFile);
	}

	std::ofstream output(path, std::ios::out | std::ios::binary);
	std::cout << "Schreibe in Mapdatei..." << std::endl;
	this->numVertices = _numVertices*4;

	//!TODO: inhaltsverzeichnis binärdatei, übergabe mehrerer Meshes, übergabe filename
	// wenn filename nicht existiert datei erstellen und reinschreiben, wenn nicht aktuelle meshNum holen
	// meshnum * bytes = offset
	// meshnum + anzahl übergebenen meshes = neue meshnum

	if (output.is_open()) {
		output.write((char*)&numVertices, sizeof(uint64));

		for (uint64 i = 0; i < numVertices; i++) {
			output.write((char*)&vd1[i].x, sizeof(float32));
			output.write((char*)&vd1[i].y, sizeof(float32));
			output.write((char*)&vd1[i].z, sizeof(float32));

			output.write((char*)&vd1[i].u, sizeof(float32));
			output.write((char*)&vd1[i].v, sizeof(float32));

			output.write((char*)&vd1[i].nx, sizeof(float32));
			output.write((char*)&vd1[i].ny, sizeof(float32));
			output.write((char*)&vd1[i].nz, sizeof(float32));



			output.write((char*)&vd2[i].x, sizeof(float32));
			output.write((char*)&vd2[i].y, sizeof(float32));
			output.write((char*)&vd2[i].z, sizeof(float32));

			output.write((char*)&vd2[i].u, sizeof(float32));
			output.write((char*)&vd2[i].v, sizeof(float32));

			output.write((char*)&vd2[i].nx, sizeof(float32));
			output.write((char*)&vd2[i].ny, sizeof(float32));
			output.write((char*)&vd2[i].nz, sizeof(float32));



			output.write((char*)&vd3[i].x, sizeof(float32));
			output.write((char*)&vd3[i].y, sizeof(float32));
			output.write((char*)&vd3[i].z, sizeof(float32));

			output.write((char*)&vd3[i].u, sizeof(float32));
			output.write((char*)&vd3[i].v, sizeof(float32));

			output.write((char*)&vd3[i].nx, sizeof(float32));
			output.write((char*)&vd3[i].ny, sizeof(float32));
			output.write((char*)&vd3[i].nz, sizeof(float32));



			output.write((char*)&vd4[i].x, sizeof(float32));
			output.write((char*)&vd4[i].y, sizeof(float32));
			output.write((char*)&vd4[i].z, sizeof(float32));

			output.write((char*)&vd4[i].u, sizeof(float32));
			output.write((char*)&vd4[i].v, sizeof(float32));

			output.write((char*)&vd4[i].nx, sizeof(float32));
			output.write((char*)&vd4[i].ny, sizeof(float32));
			output.write((char*)&vd4[i].nz, sizeof(float32));
		}
	}

	output.close();
}

void MapFileHandler::CalcMesh() {
	std::ifstream input = std::ifstream("/mapdata/pj.mapfile", std::ios::in | std::ios::binary);
	if (!input.is_open()) {
		std::cout << "Mapdatei nicht gefunden!" << std::endl;
	}

	input.read((char*)&numVertices, sizeof(uint64));

	for (uint64 i = 0; i < numVertices / 4; i++) {
		Vertex vertex, vertex2, vertex3, vertex4;

		input.read((char*)&vertex.x, sizeof(float32));
		input.read((char*)&vertex.y, sizeof(float32));
		input.read((char*)&vertex.z, sizeof(float32));

		input.read((char*)&vertex.u, sizeof(float32));
		input.read((char*)&vertex.v, sizeof(float32));

		input.read((char*)&vertex.nx, sizeof(float32));
		input.read((char*)&vertex.ny, sizeof(float32));
		input.read((char*)&vertex.nz, sizeof(float32));

		vertices.push_back(vertex);

		input.read((char*)&vertex2.x, sizeof(float32));
		input.read((char*)&vertex2.y, sizeof(float32));
		input.read((char*)&vertex2.z, sizeof(float32));

		input.read((char*)&vertex2.u, sizeof(float32));
		input.read((char*)&vertex2.v, sizeof(float32));

		input.read((char*)&vertex2.nx, sizeof(float32));
		input.read((char*)&vertex2.ny, sizeof(float32));
		input.read((char*)&vertex2.nz, sizeof(float32));

		vertices2.push_back(vertex2);

		input.read((char*)&vertex3.x, sizeof(float32));
		input.read((char*)&vertex3.y, sizeof(float32));
		input.read((char*)&vertex3.z, sizeof(float32));

		input.read((char*)&vertex3.u, sizeof(float32));
		input.read((char*)&vertex3.v, sizeof(float32));

		input.read((char*)&vertex3.nx, sizeof(float32));
		input.read((char*)&vertex3.ny, sizeof(float32));
		input.read((char*)&vertex3.nz, sizeof(float32));

		vertices3.push_back(vertex3);

		input.read((char*)&vertex4.x, sizeof(float32));
		input.read((char*)&vertex4.y, sizeof(float32));
		input.read((char*)&vertex4.z, sizeof(float32));

		input.read((char*)&vertex4.u, sizeof(float32));
		input.read((char*)&vertex4.v, sizeof(float32));

		input.read((char*)&vertex4.nx, sizeof(float32));
		input.read((char*)&vertex4.ny, sizeof(float32));
		input.read((char*)&vertex4.nz, sizeof(float32));

		vertices4.push_back(vertex4);
	}

	input.close();
	std::cout << "Mapdatei wurde gelesen!" << std::endl;
}

std::vector<Vertex> MapFileHandler::GetV1() { return vertices; };

std::vector<Vertex> MapFileHandler::GetV2() { return vertices2; }

std::vector<Vertex> MapFileHandler::GetV3() { return vertices3; }

std::vector<Vertex> MapFileHandler::GetV4() { return vertices4; }

uint64 MapFileHandler::GetNumVertices() {
	return numVertices / 4;
}