#include "Ghost.h"


enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};


void Ghost::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/Ghost.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(44, 30), glm::vec2(1 / 10.f, 0.5f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (int i = 0; i <10; ++i) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(i / 10.f, 4 / 8.f));
	}
	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (int i = 0; i < 10; ++i) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(i / 10.f, 0 / 8.f));
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	timer += rand()%300;
}
void Ghost::update(int deltaTime)
{
	if (map->collisionMoveUp(posEnemy, glm::ivec2(44, 30))) topped = true;

	int *dummy = &posEnemy.y;
	if (map->collisionMoveDown(posEnemy, glm::ivec2(44, 30), dummy)) topped = false;

	if (map->collisionMoveLeft(posEnemy, glm::ivec2(44, 30))) facing = !facing;
	else if (map->collisionMoveRight(posEnemy, glm::ivec2(44, 30))) facing = !facing;
	
	Move();
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}
void Ghost::render() {

	sprite->render();
}

void Ghost::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Ghost::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool Ghost::isColliding(glm::vec2 posPlayer) {

	if (map->collisionEnemy(posPlayer, glm::ivec2(14, 28), (posEnemy / 16), glm::ivec2(36, 28))) {
		return true;
	}
	return false;


}



void Ghost::Move() {

	timer++;

	if (timer >= 600) { 
		movement = !movement; 
		timer = 0;
		timer -= rand()%300;
	}

	if (movement) {

		posEnemy.x = posEnemy.x + 1 * facing - 1 * !facing;

	}

	else {

		if (topped) {
			posEnemy.y++;
		}
		else
			posEnemy.y--;

	}
	
	
	
	if (!facing and sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
	else if (facing and sprite->animation() !=MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
	
	return;
}