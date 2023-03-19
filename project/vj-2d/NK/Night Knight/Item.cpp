#include <iostream>
#include <cmath>
#include "Item.h"


#define DOOR_OPEN 1
#define DOOR_CLOSE 0

void Item::init()
{
	Keysheet.loadFromFile("images/Free/Items/key/key-blue2.png", TEXTURE_PIXEL_FORMAT_RGB);

	key = Sprite::createSprite(glm::ivec2(18, 18), glm::ivec2(0.833f, 1.f), &Keysheet, &texProgram);
	key->setNumberAnimations(1);
	key->setAnimationSpeed(0, 8);
	key->addKeyframe(0, glm::vec2(0.f, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 2, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 3, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 4, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 5, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 6, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 7, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 8, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 9, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 10, 0.f));
	key->addKeyframe(0, glm::vec2(0.0833f * 11, 0.f));

	Coinsheet.loadFromFile("images/Free/Items/coin/Coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	coin = Sprite::createSprite(glm::ivec2(18, 18), glm::ivec2(0.25, 1), &Coinsheet, &texProgram);
	coin->setNumberAnimations(1);
	coin->setAnimationSpeed(0, 8);
	coin->addKeyframe(0, glm::vec2(0.f, 0.f));
	coin->addKeyframe(0, glm::vec2(0.25f, 0.f));
	coin->addKeyframe(0, glm::vec2(0.5f, 0.f));
	coin->addKeyframe(0, glm::vec2(0.75f, 0.f));
	coin->changeAnimation(0);

	Doorsheet.loadFromFile("images/Free/Items/coin/Coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	door = Sprite::createSprite(glm::ivec2(18, 18), glm::ivec2(0.25, 1), &Doorsheet, &texProgram);
	door->setNumberAnimations(2);
	door->setAnimationSpeed(DOOR_CLOSE, 8);
	door->addKeyframe(0, glm::vec2(0.f, 0.f));

	door->setAnimationSpeed(DOOR_OPEN, 8);
	door->addKeyframe(0, glm::vec2(0.f, 0.f));

	door->changeAnimation(0);
}

void Item::render()
{
}