#pragma once
#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "TileMap.h"
#include "Texture.h"

class Item {

public:
	void init();
	void render();
private:
	Texture Keysheet;
	Texture Doorsheet;
	Texture Coinsheet;
	Sprite* key;
	Sprite* door;
	Sprite* coin;

#endif