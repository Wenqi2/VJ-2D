
#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include <vector>
// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

class Enemy
{
public:

	glm::vec2 pos = { 0,0 };
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
	bool loadLevel(const string& levelFile);
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;
	int Nblock = 0;
	glm::vec2 screenCoords;
	vector<glm::ivec2> positionBlock;
	glm::vec2 key_pos;
};
#endif // _TILE_MAP_INCLUDE