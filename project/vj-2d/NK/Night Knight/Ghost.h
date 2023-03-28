#ifndef _GHOST_INCLUDE
#define _GHOST_INCLUDE
#include "Vampire.h"

class Ghost
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool isColliding(glm::vec2 posPlayer);
	void Move();

	int timer = 0;

private:
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	bool facing;
	bool topped = false;
	bool movement = true;

	bool transforming = false;
	int framecounter = 0;

};

#endif
