#pragma once
#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "TileMap.h"
#include "Texture.h"

class Item {

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void collisionItem(const glm::vec2& pos);
	void render();
	void update(int deltaTime);
	void keyUP();
private:
	Texture Keysheet;
	Texture Doorsheet;
	Texture Coinsheet;
	Sprite* key;
	Sprite* door;
	Sprite* coin;
	int SCREEN_X;
	int SCREEN_Y;
	bool Bkey = true;
	bool Bcoin = true;
	bool Bdoor = false;
	glm::ivec2 tileMapDispl;
	TileMap* map;
};

#endif