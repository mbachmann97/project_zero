#include "block.h"

Block::Block() {
	this->tempVertices = new Vertex[this->numVertices];
}

void Block::CreateNewBlock(Position startVertex, int16 blockType, float32 texturesPerRow, float32 texturesPerColumn) {
	this->start = startVertex;
	this->type = blockType;
	this->texStepX = 1.0f / texturesPerRow;
	this->texStepY = 1.0f / texturesPerColumn;
	this->faces = new BlockFace[6];
	GetUvFromBlockType();
	CalcVertices();
}

void Block::GetUvFromBlockType() {
	switch (type) {
	case 0: //Dirt Block
		textureSide.u = 0.0f;
		textureSide.v = 0.0f;
		textureTop.u = 0.0f;
		textureTop.v = 0.0f;
		textureBottom.u = 0.0f;
		textureBottom.v = 0.0f;
		break;
	case 1: //Grass Block
		textureSide.u = 0.25f;
		textureSide.v = 0.0f;
		textureTop.u = 0.5f;
		textureTop.v = 0.0f;
		textureBottom.u = 0.0f;
		textureBottom.v = 0.0f;
		break;
	}
}

void Block::CalcVertices() {

	faces[0] = BlockFace{	//FRONT
		Triangle{
			Vertex{start.x, start.y, start.z, textureSide.u, textureSide.v, 0.0f, 0.0f, -1.0f},
			Vertex{start.x + scale, start.y, start.z, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, -1.0f},
			Vertex{start.x, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f}
		},
		Triangle{
			Vertex{start.x, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f},
			Vertex{start.x + scale, start.y, start.z, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, -1.0f},
			Vertex{start.x + scale, start.y + scale, start.z, textureSide.u + texStepX, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f}
		}
	};

	faces[1] = BlockFace{	//RIGHT
		Triangle{
			Vertex{start.x + scale, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f},
			Vertex{start.x + scale, start.y, start.z, textureSide.u, textureSide.v, 1.0f, 0.0f, 0.0f},
			Vertex{start.x + scale, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 1.0f, 0.0f, 0.0f}
		},
		Triangle{
			Vertex{start.x + scale, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 1.0f, 0.0f, 0.0f},
			Vertex{start.x + scale, start.y + scale, start.z - scale, textureSide.u + texStepX, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f},
			Vertex{start.x + scale, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f}
		}
	};

	faces[2] = BlockFace{	//BACK
		Triangle{
			Vertex{start.x + scale, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f},
			Vertex{start.x + scale, start.y, start.z - scale, textureSide.u, textureSide.v, 0.0f, 0.0f, 1.0f},
			Vertex{start.x, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, 1.0f}
		},
		Triangle{
			Vertex{start.x, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, 1.0f},
			Vertex{start.x, start.y + scale, start.z - scale, textureSide.u + texStepX, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f},
			Vertex{start.x + scale, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f}
		}
	};

	faces[3] = BlockFace{	//LEFT
		Triangle{
			Vertex{start.x, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f},
			Vertex{start.x, start.y, start.z - scale, textureSide.u, textureSide.v, -1.0f, 0.0f, 0.0f},
			Vertex{start.x, start.y, start.z, textureSide.u + texStepX, textureSide.v, -1.0f, 0.0f, 0.0f}
		},
		Triangle{
			Vertex{start.x, start.y, start.z, textureSide.u + texStepX, textureSide.v, -1.0f, 0.0f, 0.0f},
			Vertex{start.x, start.y + scale, start.z, textureSide.u + texStepX, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f},
			Vertex{start.x, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f}
		}
	};

	faces[4] = BlockFace{	//TOP
		Triangle{
			Vertex{start.x, start.y + scale, start.z, textureTop.u, textureTop.v, 0.0f, 1.0f, 0.0f},
			Vertex{start.x + scale, start.y + scale, start.z - scale, textureTop.u + texStepX, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f},
			Vertex{start.x, start.y + scale, start.z - scale, textureTop.u, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f}
		},
		Triangle{
			Vertex{start.x + scale, start.y + scale, start.z - scale, textureTop.u + texStepX, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f},
			Vertex{start.x, start.y + scale, start.z, textureTop.u, textureTop.v, 0.0f, 1.0f, 0.0f},
			Vertex{start.x + scale, start.y + scale, start.z, textureTop.u + texStepX, textureTop.v, 0.0f, 1.0f, 0.0f}
		}
	};

	faces[5] = BlockFace{	//BOTTOM
		Triangle{
			Vertex{start.x, start.y, start.z, textureBottom.u, textureBottom.v, 0.0f, -1.0f, 0.0f},
			Vertex{start.x, start.y, start.z - scale, textureBottom.u, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f},
			Vertex{start.x + scale, start.y, start.z - scale, textureBottom.u + texStepX, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f}
		},
		Triangle{
			Vertex{start.x + scale, start.y, start.z - scale, textureBottom.u + texStepX, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f},
			Vertex{start.x + scale, start.y, start.z, textureBottom.u + texStepX, textureBottom.v, 0.0f, -1.0f, 0.0f},
			Vertex{start.x, start.y, start.z, textureBottom.u, textureBottom.v, 0.0f, -1.0f, 0.0f}
		}
	};



	/*tempVertices[0] = Vertex{ start.x, start.y, start.z, textureSide.u, textureSide.v, 0.0f, 0.0f, -1.0f }; ---										//FRONT
	tempVertices[1] = Vertex{ start.x + scale, start.y, start.z, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, -1.0f };	---							//FRONT
	tempVertices[2] = Vertex{ start.x, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f };	---							//FRONT
	tempVertices[3] = Vertex{ start.x, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f };	---							//FRONT
	tempVertices[4] = Vertex{ start.x + scale, start.y, start.z, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, -1.0f };	---							//FRONT
	tempVertices[5] = Vertex{ start.x + scale, start.y + scale, start.z, textureSide.u + texStepX, textureSide.v + texStepY, 0.0f, 0.0f, -1.0f }; ---			//FRONT
	tempVertices[6] = Vertex{ start.x + scale, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f }; ---						//RIGHT
	tempVertices[7] = Vertex{ start.x + scale, start.y, start.z, textureSide.u, textureSide.v, 1.0f, 0.0f, 0.0f };	---										//RIGHT
	tempVertices[8] = Vertex{ start.x + scale, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 1.0f, 0.0f, 0.0f };	---					//RIGHT
	tempVertices[9] = Vertex{ start.x + scale, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 1.0f, 0.0f, 0.0f }; ---						//RIGHT
	tempVertices[10] = Vertex{ start.x + scale, start.y + scale, start.z - scale, textureSide.u + texStepX, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f };---	//RIGHT
	tempVertices[11] = Vertex{ start.x + scale, start.y + scale, start.z, textureSide.u, textureSide.v + texStepY, 1.0f, 0.0f, 0.0f };	---					//RIGHT
	tempVertices[12] = Vertex{ start.x + scale, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f };	---			//BACK
	tempVertices[13] = Vertex{ start.x + scale, start.y, start.z - scale, textureSide.u, textureSide.v, 0.0f, 0.0f, 1.0f };	---								//BACK
	tempVertices[14] = Vertex{ start.x, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, 1.0f };	---							//BACK
	tempVertices[15] = Vertex{ start.x, start.y, start.z - scale, textureSide.u + texStepX, textureSide.v, 0.0f, 0.0f, 1.0f };	---							//BACK
	tempVertices[16] = Vertex{ start.x, start.y + scale, start.z - scale, textureSide.u + texStepX, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f };	 ---		//BACK
	tempVertices[17] = Vertex{ start.x + scale, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, 0.0f, 0.0f, 1.0f }; ---				//BACK
	tempVertices[18] = Vertex{ start.x, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f };	---					//LEFT
	tempVertices[19] = Vertex{ start.x, start.y, start.z - scale, textureSide.u, textureSide.v, -1.0f, 0.0f, 0.0f };	---									//LEFT
	tempVertices[20] = Vertex{ start.x, start.y, start.z, textureSide.u + texStepX, textureSide.v, -1.0f, 0.0f, 0.0f };	---									//LEFT
	tempVertices[21] = Vertex{ start.x, start.y, start.z, textureSide.u + texStepX, textureSide.v, -1.0f, 0.0f, 0.0f };	---									//LEFT
	tempVertices[22] = Vertex{ start.x, start.y + scale, start.z, textureSide.u + texStepX, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f };	---				//LEFT
	tempVertices[23] = Vertex{ start.x, start.y + scale, start.z - scale, textureSide.u, textureSide.v + texStepY, -1.0f, 0.0f, 0.0f };	---					//LEFT
	tempVertices[24] = Vertex{ start.x, start.y + scale, start.z, textureTop.u, textureTop.v, 0.0f, 1.0f, 0.0f }; ---											//TOP
	tempVertices[25] = Vertex{ start.x + scale, start.y + scale, start.z - scale, textureTop.u + texStepX, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f }; ---		//TOP
	tempVertices[26] = Vertex{ start.x, start.y + scale, start.z - scale, textureTop.u, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f }; ---						//TOP
	tempVertices[27] = Vertex{ start.x + scale, start.y + scale, start.z - scale, textureTop.u + texStepX, textureTop.v + texStepY, 0.0f, 1.0f, 0.0f };	---	//TOP
	tempVertices[28] = Vertex{ start.x, start.y + scale, start.z, textureTop.u, textureTop.v, 0.0f, 1.0f, 0.0f };	---										//TOP
	tempVertices[29] = Vertex{ start.x + scale, start.y + scale, start.z, textureTop.u + texStepX, textureTop.v, 0.0f, 1.0f, 0.0f };	---					//TOP
	tempVertices[30] = Vertex{ start.x, start.y, start.z, textureBottom.u, textureBottom.v, 0.0f, -1.0f, 0.0f };	---										//BOTTOM
	tempVertices[31] = Vertex{ start.x, start.y, start.z - scale, textureBottom.u, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f };	---						//BOTTOM
	tempVertices[32] = Vertex{ start.x + scale, start.y, start.z - scale, textureBottom.u + texStepX, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f }; ---		//BOTTOM
	tempVertices[33] = Vertex{ start.x + scale, start.y, start.z - scale, textureBottom.u + texStepX, textureBottom.v + texStepY, 0.0f, -1.0f, 0.0f };	---	//BOTTOM
	tempVertices[34] = Vertex{ start.x + scale, start.y, start.z, textureBottom.u + texStepX, textureBottom.v, 0.0f, -1.0f, 0.0f };	---						//BOTTOM
	tempVertices[35] = Vertex{ start.x, start.y, start.z, textureBottom.u, textureBottom.v, 0.0f, -1.0f, 0.0f };	*/										//BOTTOM
};

BlockFace* Block::GetFaces() {
	return faces;
}

