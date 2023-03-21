
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


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
	block2 = Sprite::createSprite(glm::ivec2(tileSize, tileSize), glm::ivec2(0.5, 0.5), &Blocsheet, &texProgram);
	block2->setNumberAnimations(1);
	block2->setAnimationSpeed(0, 8);
	block2->addKeyframe(0, glm::vec2(0.5f, 0.f));
	block2->changeAnimation(0);

	Trapsheet.loadFromFile("images/spike.png", TEXTURE_PIXEL_FORMAT_RGBA);
	trap = Sprite::createSprite(glm::ivec2(tileSize, tileSize), glm::ivec2(1, 1), &Trapsheet, &texProgram);
	trap->setNumberAnimations(1);
	trap->setAnimationSpeed(0, 8);
	trap->addKeyframe(0, glm::vec2(0.f, 0.f));
	trap->changeAnimation(0);

	Backsheet.loadFromFile("images/back3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgound = Sprite::createSprite(glm::ivec2(576, 464), glm::ivec2(1, 1), &Backsheet, &texProgram);
	backgound->setNumberAnimations(1);
	backgound->setAnimationSpeed(0, 8);
	backgound->addKeyframe(0, glm::vec2(0.f, 0.f));
	backgound->changeAnimation(0);

	//item = new Item();
	//item -> init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);

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

	int i = map->getNblock(); //item->keyUP();

	//item->collisionItem(player->getposPlayer());
	//item->update(deltaTime);

	if (map->collisionTrap(player ->getposPlayer(), glm::ivec2(32, 32))) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
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
	player->render();
	//item->render();
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
  
  
	//int len  = skeletons.size();
	//for (int i = 0; i < len; i++) {
	//	skeletons[i]->render();
	//	
	//}

	

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

