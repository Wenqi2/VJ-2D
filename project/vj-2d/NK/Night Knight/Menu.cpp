#include "Menu.h"
#include "Game.h"
#include <GL/freeglut_std.h>
#include <iostream>

void Menu::init(ShaderProgram& texProgram)
{
	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menu = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.0, 1.0), &spritesheet, &texProgram);

	texIns.loadFromFile("images/instruction.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.0, 1.0), &texIns, &texProgram);

	texCred.loadFromFile("images/credit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	credits = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.0, 1.0), &texCred, &texProgram);

	texArrow.loadFromFile("images/arrow.png", TEXTURE_PIXEL_FORMAT_RGBA);
	arrow = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1.0, 1.0), &texArrow, &texProgram);
	delay = 12;
}

void Menu::render()
{
	switch (level)
	{
	case 0:
		menu->render();
		arrow->render();
		arrow->setPosition(glm::vec2(50.0f, 50.0f + cursor * 36.0f));
		break;
	case 1:
		instructions->render();
		break;
	case 2:
		credits->render();
		break;
	default:
		break;
	}
}

void Menu::update(int deltaTime)
{
	++delay;
	switch (level)
	{
	case 0:
		menu->update(deltaTime);
		arrow->update(deltaTime);
		break;
	case 1:
		instructions->update(deltaTime);
		break;
	case 2:
		credits->update(deltaTime);
		break;
	default:
		break;
	}
	if (delay >= 15)
	{

		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && level == 0) {
			delay = 0;
			if (cursor <= 0) cursor = 0;
			else {
				cursor--;
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && level == 0) {
			delay = 0;
			if (cursor >= 2) cursor = 2;
			else {
				cursor++;
			}
		}
		else if (Game::instance().getKey(13)) 
		{
			delay = 0;
			if (level != 0) {
				level = 0;
			}
			else {
				switch (cursor) {
				case 0:	//PLAY
					Game::instance().initScene();
					break;
				case 1: //INSTRUCTIONS
					level = 1;
					instructions->setPosition(glm::vec2(0.0f, 0.0f)); //Show Instructions
					break;
				case 2: //Credit
					level = 2;
					credits->setPosition(glm::vec2(0.0f, 0.0f)); //Show Instructions
					break;

				}
			}
		}
		arrow->setPosition(glm::vec2(50.0f, 50.0f + cursor * 36.0f));
	}
}
