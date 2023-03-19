
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

	Blocsheet.loadFromFile("images/Free/Terrain/bloc.png", TEXTURE_PIXEL_FORMAT_RGBA);
	block2 = Sprite::createSprite(glm::ivec2(tileSize, tileSize), glm::ivec2(0.5, 0.5), &Blocsheet, &texProgram);
	block2->setNumberAnimations(1);
	block2->setAnimationSpeed(0, 8);
	block2->addKeyframe(0, glm::vec2(0.f, 0.f));
	block2->changeAnimation(0);

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

	coin->changeAnimation(0);



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
	for (int i = 0; i < len; ++i) {
		skeletons[i]->update(deltaTime);
	}

}

void Scene::update_map(int deltaTime)
{
	map->render();
}



void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	int tileSize = map->getTileSize();

	coin->setPosition(glm::vec2(SCREEN_X + map->getposCoin().x * tileSize, SCREEN_Y + map->getposCoin().y * tileSize));
	coin->render();

	if (Bkey) {
		key->setPosition(glm::vec2(SCREEN_X + map->getposKey().x * tileSize, SCREEN_Y + map->getposKey().y * tileSize));
		key->render();
	}

	vector<glm::ivec2> positionBlock = map ->getpositionBlock();
	for (auto p : positionBlock)
	{
		block2->changeAnimation(0);
		block2->setPosition(glm::vec2(SCREEN_X + p[0] * tileSize, SCREEN_Y + p[1] * tileSize));
		block2->render();
	}
  
  
	int len  = skeletons.size();
	for (int i = 0; i < len; i++) {
		skeletons[i]->render();
		
	}
	
	//if (map->getNblock() == 0) doorOpen = true;

	if (doorOpen) {
		door->changeAnimation(DOOR_OPEN);
		door->setPosition(glm::vec2(SCREEN_X + map->getposDoor().x * tileSize, SCREEN_Y + map->getposDoor().y * tileSize));
		door->render();
	}
	else {
		door->setPosition(glm::vec2(SCREEN_X + map->getposDoor().x * tileSize, SCREEN_Y + map->getposDoor().y * tileSize));
		door->render();
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

