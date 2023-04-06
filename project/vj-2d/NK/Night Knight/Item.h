#pragma once
#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "TileMap.h"
#include "Texture.h"
#include "SoundManager.h"

class Item {

public:
	void key_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void door_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void hourglass_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void coin_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void clock_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	void arrow_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map);
	bool collisionItem(const glm::vec2& pos);
	void render();
	void update(int deltaTime);
	void keyUP();
	void doorOpen();

private:
	SoundManager sound;
	Texture Spritesheet;
	Sprite* sprite;

	int SCREEN_X;
	int SCREEN_Y;
	bool Bkey = true;
	bool Bcoin = true;
	bool Bdoor = false;
	glm::ivec2 tileMapDispl;
	TileMap* map;
	glm::vec2 sizeItem;
	glm::vec2 posItem;
};

#endif