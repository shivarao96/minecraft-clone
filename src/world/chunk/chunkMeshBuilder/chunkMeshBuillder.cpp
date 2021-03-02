#include "chunkMeshBuillder.h"
#include <vector>
#include "../../Block/blockDataBase/blockDataBase.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace FaceVal {
	
	std::vector<float> frontFace{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	std::vector<float> backFace{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	std::vector<float> leftFace{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	std::vector<float> rightFace{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	std::vector<float> topFace{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	std::vector<float> bottomFace{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

}

struct Direction
{
	void update(int x, int y, int z) {
		up    = { x    , y + 1, z     };
		down  = { x    , y - 1, z     };
		left  = { x - 1, y    , z     };
		right = { x + 1, y    , z     };
		front = { x    , y    , z + 1 };
		back  = { x    , y    , z - 1 };
	}

	sf::Vector3i up;
	sf::Vector3i down;
	sf::Vector3i left;
	sf::Vector3i right;
	sf::Vector3i front;	
	sf::Vector3i back;
};

ChunkMeshBuillder::ChunkMeshBuillder(const ChunkSection& chunkSection, ChunkMesh& chunkMesh)
	:m_pChunkSection(&chunkSection)
	,m_pChunkMesh(&chunkMesh)
{}

void ChunkMeshBuillder::buildMesh() {
	sf::Clock c;
	Direction direction;

	for (int8_t y = 0; y < CHUNK_SIZE; ++y) {
		for (int8_t x = 0; x < CHUNK_SIZE; ++x) {
			for (int8_t z = 0; z < CHUNK_SIZE; ++z) {
				sf::Vector3i positions(x,y,z);
				ChunkBlock block = m_pChunkSection->getBlock(x, y, z);
				if (block == BlockId::AIR) {
					continue;
				}

				m_pBlockDataHolder = &block.getBlockData().getBlockData();
				auto& texData = *m_pBlockDataHolder;
				direction.update(x, y, z);

				// now try adding all the faces
				
				tryAddFaceToMesh(
					FaceVal::topFace,
					texData.texTopCoords,
					positions,
					direction.up,
					"up"
				);
				tryAddFaceToMesh(
					FaceVal::bottomFace,
					texData.texBottomCoords,
					positions,
					direction.down,
					"down"
				);
				tryAddFaceToMesh(
					FaceVal::leftFace,
					texData.texSideCoords,
					positions,
					direction.left,
					"left"
				);
				tryAddFaceToMesh(
					FaceVal::rightFace,
					texData.texSideCoords,
					positions,
					direction.right,
					"right"
				);
				tryAddFaceToMesh(
					FaceVal::frontFace,
					texData.texSideCoords,
					positions,
					direction.front,
					"front"
				);
				tryAddFaceToMesh(
					FaceVal::backFace,
					texData.texSideCoords,
					positions,
					direction.back,
					"back"
				);
			}
		}
	}
}

void ChunkMeshBuillder::tryAddFaceToMesh(
	const std::vector<float>& blockFace,
	const sf::Vector2i& texCoords,
	const sf::Vector3i& chunkPosition,
	const sf::Vector3i& blockPosition,
	const char* faceType
) {
	if (shouldMakeFace(blockPosition, *m_pBlockDataHolder, faceType)) {
		auto texCoordInfo = BlockDataBase::get().m_textureAtlas.getTextureCoords(texCoords);
		m_pChunkMesh->addFace(
			blockFace,
			texCoordInfo,
			m_pChunkSection->getLocation(),
			chunkPosition
		);
	}
}

bool ChunkMeshBuillder::shouldMakeFace(
	const sf::Vector3i& adjPositions,
	const BlockDataHolder& blockdata,
	const char* faceType
) {
	auto block = m_pChunkSection->getBlock(
		adjPositions.x,
		adjPositions.y,
		adjPositions.z
	);
	if (block == BlockId::AIR) {
		return true;
	}
	else {
		return false;
	}
}

ChunkMeshBuillder::~ChunkMeshBuillder() {
	//delete m_pChunkMesh;
	//delete m_pChunkSection;
	//delete m_pBlockDataHolder;
}