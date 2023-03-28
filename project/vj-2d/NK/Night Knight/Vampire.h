#ifndef _VAMPIRE_INCLUDE
#define _VAMPIRE_INCLUDE
#include "Skeleton.h"

class Vampire
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool isColliding(glm::vec2 posPlayer);

	void Transform();
	void Move();

private:
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool facing;
	bool topped = false;
	int cooldown = 0;
	
	int state;
	bool transforming = false;
	int framecounter = 0;


};

#endif
