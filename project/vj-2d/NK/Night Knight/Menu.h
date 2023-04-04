#pragma once
#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Texture.h"
#include "TileMap.h"
#include <glm/glm.hpp>
#include "SoundManager.h"


class Menu {

public:
	void init(ShaderProgram& texProgram);
	void render();
	void update(int deltaTime);

private:
	SoundManager sound;
	Texture spritesheet, texMenu, texIns, texCred, texArrow;
	Sprite* menu, * instructions, * credits, *arrow;
	int cursor = 0;
	bool bMenu = true;
	bool bIns = false;
	bool bCred = false;
	int level = 0;
	int delay ;
};
#endif