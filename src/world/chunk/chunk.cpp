#include "chunk.h"
#include "../world.h"
#include "../Block/chunkBlock/chunkBlock.h"
#include "../../renderer/mainRenderer.h"
#include "chunkMeshBuilder/chunkMeshBuillder.h"
#include <iostream>

Chunk::Chunk(World& world, sf::Vector2i location):m_location(location),m_pWorld(&world) {
	//load();
}

void Chunk::load() {
	for (int y = 0; y < 3; y++) {
		m_chunksSections.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
	}
	int height = m_chunksSections.size() * CHUNK_SIZE;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				if (y == height - 1) {
					setBlock(x, y, z, BlockId::GRASS);
				}
				else if (y > height / 3 && y < height - 1) {
					setBlock(x, y, z, BlockId::DIRT);
				}
				else {
					setBlock(x, y, z, BlockId::STONE);
				}
			}
		}

	}
	m_chunkLoaded = true;
}

bool Chunk::hasLoaded() {
	return m_chunkLoaded;
}

bool Chunk::makeMesh() {
	for (auto& chunkSection: m_chunksSections) {
		if (!chunkSection.hasMesh()) { //if mesh don't exist then make the mesh
			chunkSection.makeMesh(); 
			return true;
		}
	}
	return false;
}
void Chunk::setBlock(int x, int y, int z, ChunkBlock block) {
	if (outOfBound(x, y, z)) return;
	int bY = y % CHUNK_SIZE;
	m_chunksSections.at(y / CHUNK_SIZE).setBlock(x, bY, z, block);
}
ChunkBlock Chunk::getBlock(int x, int y, int z) const {
	if (outOfBound(x, y, z)) { 
		return BlockId::AIR; 
	}
	int bY = y % CHUNK_SIZE;
	return m_chunksSections.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}
void Chunk::drawChunks(MainRenderer& renderer) const {
	for (const auto& chunkSection : m_chunksSections) {
		if (chunkSection.hasMesh()) {
			renderer.drawChunk(chunkSection.m_chunkMesh);
		}
	}
}
bool Chunk::outOfBound(int x, int y, int z) const {
	if (x >= CHUNK_SIZE) {
		std::cout << "x size greater than chunk_size" << std::endl;
		return true;
	} 
	if (z >= CHUNK_SIZE) {
		std::cout << "z size greater than chunk_size" << std::endl;
		return true;
	}

	if (x < 0) return true;
	if (y < 0) return true;
	if (z < 0) return true;

	if (y >= (int)m_chunksSections.size() * CHUNK_SIZE) {
		return true;
	}
	
	return false;
}

ChunkSection& Chunk::getSection(int index) {
	while (index >= m_chunksSections.size()) {
		// create new section
		m_chunksSections.emplace_back(sf::Vector3i(m_location.x, m_chunksSections.size(), m_location.y), *m_pWorld);
	}
	return m_chunksSections.at(index);
}