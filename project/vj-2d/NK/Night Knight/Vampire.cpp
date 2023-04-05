#include "Vampire.h"

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT, FLY_LEFT, FLY_RIGHT, TO_VAMPIRE_LEFT, TO_VAMPIRE_RIGHT, TO_BAT_LEFT, TO_BAT_RIGHT
};

enum States {

	INIT, VAMPIRE, BAT_TRANS, BAT, VAMP_TRANS

};

void Vampire::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/Vampire.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(37, 30), glm::vec2(1/20.f,1/8.f), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (int i = 19; i >= 0; --i) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(i / 20.f, 0 / 8.f));
	}
	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (int i = 0; i < 20; ++i) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(i / 20.f, 4 / 8.f));
	}
	
	
	sprite->setAnimationSpeed(FLY_RIGHT, 5);
	for (int i = 10; i >= 0; --i) {
		sprite->addKeyframe(FLY_RIGHT, glm::vec2(i / 20.f, 1 / 8.f));
	}
	sprite->setAnimationSpeed(FLY_LEFT, 5);
	for (int i = 9 ; i < 20 ; ++i) {
		sprite->addKeyframe(FLY_LEFT, glm::vec2(i / 20.f, 5 / 8.f));
	}
	
	sprite->setAnimationSpeed(TO_BAT_RIGHT,9);
	for (int i = 19 ; i > 10; --i) {
		sprite->addKeyframe(TO_BAT_RIGHT, glm::vec2( (i/20.f), (1 / 8.f)));
	}
	sprite->setAnimationSpeed(TO_BAT_LEFT, 9);
	for (int i = 0; i < 9 ; ++i) {
		sprite->addKeyframe(TO_BAT_LEFT, glm::vec2((i/20.f), (5 / 8.f)));
	}
	
	sprite->setAnimationSpeed(TO_VAMPIRE_RIGHT, 20);
	for (int j = 2; j < 4; ++j) {
		for (int i = 19; i >= 0; --i) {
			sprite->addKeyframe(TO_VAMPIRE_RIGHT, glm::vec2( i/ 20.f, j / 8.f));
			if (i == 10 and j == 3) {
				i = -1;
				j = 4;
			}
		}
	}
	sprite->setAnimationSpeed(TO_VAMPIRE_LEFT, 20);
	for (int j = 6; j < 8; ++j) {
		for (int i = 0; i < 20; ++i) {
			sprite->addKeyframe(TO_VAMPIRE_LEFT, glm::vec2( i / 20.f, j / 8.f));
			if (i == 9 and j == 7) {
				i = 20;
				j = 8;
			}
		
		}
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

	state = INIT;


	

}
void Vampire::update(int deltaTime)
{

	int bullshyt = posEnemy.y;
	switch (state)
	{
	case INIT:
		
		if (!map->collisionMoveDown(posEnemy, glm::vec2(26,30), &posEnemy.y)) {
			posEnemy.y++;
		}
		else state = VAMPIRE;
		
		
		break;
	case VAMPIRE:
 		

		if (map->collisionMoveLeft(posEnemy, glm::ivec2(26, 29))) {
			facing = !facing;
		}
		else if (map->collisionMoveRight(posEnemy, glm::ivec2(26, 29))) {
			facing = !facing;
		}
		
		if (!map->collisionMoveDown(posEnemy, glm::ivec2(26, 30), &bullshyt)){
		
				
				state = BAT_TRANS;
			
		}
		Move();
		
		break;
	case BAT_TRANS:

		transforming = true;
		Transform();
		topped = false;
		if (map->collisionMoveDown(posEnemy, glm::ivec2(26, 30), &bullshyt)) posEnemy.y--;
		if (!transforming) state = BAT;

		break;
	case BAT:
	
		if (map->collisionMoveUp(posEnemy, glm::ivec2(26, 30))) topped = true;

		else if (map->collisionMoveLeft(glm::vec2(posEnemy.x-1, posEnemy.y), glm::ivec2(26, 29))) {
			facing = !facing;
		}
		else if (map->collisionMoveRight(posEnemy, glm::ivec2(30, 29))) {
			facing = !facing;
		}
		else if (map->collisionTrap(posEnemy, glm::ivec2(26, 29))) topped = false;
		

		Move();
		if (map->collisionMoveDown(posEnemy, glm::ivec2(26, 30), &bullshyt)) {
		
				state = VAMP_TRANS;
			
		}
		
		break;
	case VAMP_TRANS:
		
		transforming = true;
		Transform();
		if (!transforming) { 
				state = VAMPIRE;
		}
		while (map->collisionMoveDown(posEnemy, glm::ivec2(26, 30), &bullshyt)) {
			posEnemy.y--;
		}
		posEnemy.y++;
		
		break;
	default:
		break;
	}

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}
void Vampire::render() {

	sprite->render();
}

void Vampire::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Vampire::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool Vampire::isColliding(glm::vec2 posPlayer) {

	if (map->collisionEnemy(posPlayer, glm::ivec2(14, 28), (posEnemy / 16), glm::ivec2(36, 28))) {
		return true;
	}
	return false;


}

void Vampire::Transform() {

	if (framecounter == 0) {
		if (state == VAMP_TRANS) {
			if (!facing and sprite->animation() != TO_VAMPIRE_LEFT) {

				sprite->changeAnimation(TO_VAMPIRE_LEFT);
			}
			else if (facing and sprite->animation() != TO_VAMPIRE_RIGHT) {
				sprite->changeAnimation(TO_VAMPIRE_RIGHT);
			}
		}
		else if (state == BAT_TRANS){
			if (!facing and sprite->animation() != TO_BAT_LEFT) {
				sprite->changeAnimation(TO_BAT_LEFT);
			}
			else if (facing and sprite->animation() != TO_BAT_RIGHT) {
				sprite->changeAnimation(TO_BAT_RIGHT);
			}
		}
	}
	framecounter++;

	if (state == BAT_TRANS) {
		if (framecounter > 50) {
			transforming = false;
			framecounter = 0;
			state = BAT;
		}
	}
	else if (state == VAMP_TRANS) {
		if (framecounter > 85) {
			transforming = false;
			state = VAMPIRE;
			framecounter = 0;
		}
	}
	return;

}

void Vampire::Move() {

	if (state == BAT) {
		posEnemy.x = posEnemy.x + 1*facing - 1*!facing;


		if (topped) {
			posEnemy.y++;
		}
		else
			posEnemy.y--;
		
		if (!facing and sprite->animation() != FLY_LEFT) sprite->changeAnimation(FLY_LEFT);



		else if (facing and sprite->animation() != FLY_RIGHT) sprite->changeAnimation(FLY_RIGHT);
	}
	else if (state == VAMPIRE) {
		posEnemy.x = posEnemy.x + 1 * facing - 1 * !facing;
		if (!facing) sprite->changeAnimation(MOVE_LEFT);
		else sprite->changeAnimation(MOVE_RIGHT);
	}
	

	return;
}