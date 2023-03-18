#include <iostream>
#include "Skeleton.h"



enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};

void Skeleton::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){

	spritesheet.loadFromFile("images/Enemies/AngryPig/AngryPig.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(36, 30), glm::vec2(0.0, 0.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_LEFT, 16);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(1 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(2 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(3 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(4 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(5 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(6 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(7 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(8 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(9 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(10 * 0.0625, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(11 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(12 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(13 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(14 * 0.0625f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(15 * 0.0625f, 0.f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 16);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(10 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(11 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(12 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(13 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(14 * 0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(15 * 0.0625f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));


}
void Skeleton::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (facing) {
		posEnemy.x += 1;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(36, 30))) {
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
			facing = !facing;
		}
		else if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			

	}

	else {
		posEnemy.x -= 1;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(36, 30))) {
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
			facing = !facing;
		}
		else if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}
void Skeleton::render(){

	sprite->render();
}

void Skeleton::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Skeleton::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}