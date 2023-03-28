
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

#define DOOR_OPEN 1
#define DOOR_CLOSE 0


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}



void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	int tileSize = map->getTileSize();
  

	int len = map->enemies.size();
	
	for (int i = 0; i < len; ++i) {
		skeleton = new Skeleton();
		skeleton->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton->setPosition(glm::vec2(map->enemies[i].pos.x * map->getTileSize(), map->enemies[i].pos.y * map->getTileSize()));
		skeleton->setTileMap(map);
		skeletons.push_back(skeleton);
	}

	Blocsheet.loadFromFile("images/bloc.png", TEXTURE_PIXEL_FORMAT_RGBA);
	block2 = Sprite::createSprite(glm::ivec2(tileSize, tileSize), glm::vec2(0.5, 0.5), &Blocsheet, &texProgram);
	block2->setNumberAnimations(1);
	block2->setAnimationSpeed(0, 8);
	block2->addKeyframe(0, glm::vec2(0.f, 0.5f));
	block2->changeAnimation(0);

	Trapsheet.loadFromFile("images/spike.png", TEXTURE_PIXEL_FORMAT_RGBA);
	trap = Sprite::createSprite(glm::ivec2(tileSize, tileSize), glm::vec2(1, 1), &Trapsheet, &texProgram);
	trap->setNumberAnimations(1);
	trap->setAnimationSpeed(0, 8);
	trap->addKeyframe(0, glm::vec2(0.f, 0.f));
	trap->changeAnimation(0);

	Backsheet.loadFromFile("images/back3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgound = Sprite::createSprite(glm::ivec2(576, 464), glm::vec2(1, 1), &Backsheet, &texProgram);
	backgound->setNumberAnimations(1);
	backgound->setAnimationSpeed(0, 8);
	backgound->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgound->changeAnimation(0);

	coin = new Item();
	coin -> coin_init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
	key = new Item();
	key->key_init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
	hourglass = new Item();
	hourglass->hourglass_init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
	clock = new Item();
	clock->clock_init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
	items.push_back(coin);
	items.push_back(key);
	items.push_back(hourglass);
	items.push_back(clock);

	Doorsheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	door = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 0.5), &Doorsheet, &texProgram);
	door->setNumberAnimations(2);
	door->setAnimationSpeed(DOOR_CLOSE, 8);
	door->addKeyframe(0, glm::vec2(0.f, 0.f));

	door->setAnimationSpeed(DOOR_OPEN, 8);
	door->addKeyframe(0, glm::vec2(0.f, 0.5f));
	door->changeAnimation(DOOR_CLOSE);

	int tilesize = map->getTileSize();
	door->setPosition(glm::vec2(SCREEN_X + map->getposDoor().x * tilesize, SCREEN_Y + map->getposDoor().y * tilesize));

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}


void Scene::update(int deltaTime)
{

	currentTime += deltaTime;
	player->update(deltaTime);
	int len = skeletons.size();
	if (hourglassGet and currentTime - actual_time <= 2000) {

	}
	else {
		for (int i = 0; i < len; ++i) {
			skeletons[i]->update(deltaTime);
		}
	}

	if (map->collisionTrap(player ->getposPlayer(), glm::ivec2(32, 32))) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	}

	for (int i = 0; i < items.size(); ++i) {
		switch (i)
		{
		case 0: //COIN
			if (items[0]->collisionItem(player->getposPlayer()) && not coinGet && coinUP) {
				coinGet = true;
			}
			items[0]->update(deltaTime);

		case 1: // KEY
			
			if (items[1]->collisionItem(player->getposPlayer()) && keyUP && not keyGet) {
				keyGet = true;
				//door->changeAnimation(1);
				//door->update(deltaTime);
				doorOpen = true;
			}
			items[1]->update(deltaTime);

		case 2: // HOURGLASS
			if (items[2]->collisionItem(player->getposPlayer()) && not hourglassGet && hourglassUP) {
				hourglassGet = true;
				actual_time = currentTime;
			}
			items[2]->update(deltaTime);

		case 3: // CLOCK
			if (items[3]->collisionItem(player->getposPlayer()) && not clockGet && clockUP) {
				clockGet = true;
			}
			items[3]->update(deltaTime);

		default:
			break;
		}
	}

	

}





void Scene::render()
{
	glm::mat4 modelview;

	backgound->setPosition(glm::vec2(32, 16));
	backgound->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	door->render();
	if (not keyGet) {
		if (map->getNblock() == 0) {
			items[1]->render();
			keyUP = true;
		}
	}
	if (currentTime >= 3000 and not coinGet) { // Coin
		items[0]->render();
		coinUP = true;
	}

	if (currentTime >= 4000 and not hourglassGet) { // Hourglass
		items[2]->render();
		hourglassUP = true;
	}

	if (currentTime >= 4500 and not clockGet) { // Hourglass
		items[3]->render();
		clockUP = true;
	}
	player->render();
	int tileSize = map->getTileSize();



	vector<glm::ivec2> positionBlock = map ->getpositionBlock();
	for (auto p : positionBlock)
	{
		block2->setPosition(glm::vec2(SCREEN_X + p[0] * tileSize, SCREEN_Y + p[1] * tileSize));
		block2->render();
	}

	vector<glm::vec2> positionTrap = map->getpositionTrap();
	for (auto p : positionTrap)
	{
		trap->setPosition(glm::vec2(SCREEN_X + p.x * tileSize, SCREEN_Y + p.y * tileSize));
		trap->render();
	}
	
  
	int len  = skeletons.size();
	for (int i = 0; i < len; i++) {
		skeletons[i]->render();
		
	}

	

}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

