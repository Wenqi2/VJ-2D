	#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
using namespace std;
TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}
TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include <vector>

class Enemy	
{	
public:	
		
	glm::vec2 pos = {0,0};	
	bool facing = false;	
	char enemyType;	
		
	Enemy() {}	
	Enemy(Enemy&&) {	
	}	
	//I know what I'm doing, compiler, use the default version.	
	Enemy(const Enemy&) = default;	
	void setPos(glm::vec2 p) {	
		pos = p;	
	}	
};	

class TileMap
{
private:
	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);
public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);
	~TileMap();
	void render() const;
	void free();
	int getTileSize() const { return tileSize; }
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
  void changeColor(const glm::ivec2& pos, const glm::ivec2& size);
	vector<glm::ivec2> getpositionBlock();
	glm::vec2 getposKey();
  vector<Enemy> enemies;
  
  	private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
	int Nblock = 0;
	glm::vec2 screenCoords;
	vector<glm::ivec2> positionBlock;
	glm::vec2 key_pos;
};
#endif // _TILE_MAP_INCLUDE
