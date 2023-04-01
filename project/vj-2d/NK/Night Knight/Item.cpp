#include <iostream>
#include <cmath>
#include "Item.h"


#define DOOR_OPEN 1
#define DOOR_CLOSE 0

void Item::key_init(const glm::ivec2& tileMapPos, ShaderProgram &texProgram, TileMap* Tmap)
{
	map = Tmap;
	posItem = map->getposKey();
	sizeItem = glm::vec2(26, 20);
	Spritesheet.loadFromFile("images/key-blue.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::ivec2(26, 20), glm::vec2(0.0833f, 1.f), &Spritesheet, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 2, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 3, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 4, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 5, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 6, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 7, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 8, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 9, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 10, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0833f * 11, 0.f));
	sprite->changeAnimation(0);

	int tilesize = map->getTileSize();
	sprite->setPosition(glm::vec2(tileMapPos.x + posItem.x * tilesize, tileMapPos.y + posItem.y * tilesize - 4));


}

void Item::door_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* Tmap)
{
	map = Tmap;
	posItem = map->getposDoor();
	sizeItem = glm::vec2(32, 32);

	Spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 0.5), &Spritesheet, &texProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(DOOR_CLOSE, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(DOOR_OPEN, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.5f));

	int tilesize = map->getTileSize();
	sprite->setPosition(glm::vec2(SCREEN_X + posItem.x * tilesize, 32+SCREEN_Y + posItem.y * tilesize));
}

void Item::hourglass_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* Tmap)
{
	sizeItem = glm::vec2(16, 20);
	map = Tmap;
	posItem = map->getposHourglass();

	Spritesheet.loadFromFile("images/hourglass2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 20), glm::vec2(1, 1), &Spritesheet, &texProgram);

	int tilesize = map->getTileSize();
	sprite->setPosition(glm::vec2(tileMapPos.x + posItem.x * tilesize, tileMapPos.y + posItem.y * tilesize - 4));


}

void Item::coin_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* Tmap)
{
	map = Tmap;
	int tilesize = map->getTileSize();
	sizeItem = glm::vec2(tilesize, tilesize);
	posItem = map->getposCoin();

	Spritesheet.loadFromFile("images/Coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 1), &Spritesheet, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite->changeAnimation(0);


	sprite->setPosition(glm::vec2(tileMapPos.x + posItem.x * tilesize, tileMapPos.y + posItem.y * tilesize));
	
}

void Item::clock_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* Tmap)
{
	sizeItem = glm::vec2(22, 18);
	map = Tmap;
	posItem = map->getposClock();

	Spritesheet.loadFromFile("images/clock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(22, 18), glm::vec2(1, 1), &Spritesheet, &texProgram);

	int tilesize = map->getTileSize();
	sprite->setPosition(glm::vec2(tileMapPos.x + posItem.x * tilesize, tileMapPos.y + posItem.y * tilesize - 2));
}

void Item::arrow_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* map)
{
}

bool Item::collisionItem(const glm::vec2& posPlayer)
{	
	return map->collisionItem(posPlayer, glm::ivec2(32, 32), posItem, sizeItem); 

}

void Item::render()
{
	sprite->render();

}

void Item::update(int deltaTime)
{
	sprite->update(deltaTime);
}


void Item::keyUP()
{
	Bkey = true;
}

void Item::doorOpen()
{
	sprite->changeAnimation(1);
}
