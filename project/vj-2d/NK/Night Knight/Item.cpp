#include <iostream>
#include <cmath>
#include "Item.h"


#define DOOR_OPEN 1
#define DOOR_CLOSE 0

void Item::key_init(const glm::ivec2& tileMapPos, ShaderProgram &texProgram, TileMap* Tmap)
{
	map = Tmap;
	posItem = map->getposKey();
	Spritesheet.loadFromFile("images/key-blue.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::ivec2(22, 16), glm::vec2(0.0833f, 1.f), &Spritesheet, &texProgram);
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
	sprite->setPosition(glm::vec2(tileMapPos.x + map->getposKey().x * tilesize, tileMapPos.y + map->getposKey().y * tilesize));
	sizeItem = glm::vec2(22, 16);

}

void Item::hourglass_init(const glm::ivec2& tileMapPos, ShaderProgram& texProgram, TileMap* Tmap)
{
	sizeItem = glm::vec2(16, 21);
	map = Tmap;
	posItem = map->getposHourglass();

	Spritesheet.loadFromFile("images/hourglass.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 21), glm::vec2(1, 1), &Spritesheet, &texProgram);

	int tilesize = map->getTileSize();
	sprite->setPosition(glm::vec2(tileMapPos.x + map->getposHourglass().x * tilesize, tileMapPos.y + map->getposHourglass().y * tilesize));


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


	sprite->setPosition(glm::vec2(tileMapPos.x + map->getposCoin().x * tilesize, tileMapPos.y + map->getposCoin().y * tilesize));
	
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
