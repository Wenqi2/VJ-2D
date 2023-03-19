#ifndef _SKELETON_INCLUDE
#define _SKELETON_INCLUDE



#include "Player.h"

class Skeleton {


public:
	
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private: 
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool facing; 

};

#endif