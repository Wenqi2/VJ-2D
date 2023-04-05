
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 32

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



void Scene::init(int level)
{
	initShaders();
	delay_start = 0;
	keyUP = false;
	keyGet = false;
	coinUP = false;
	coinGet = false;
	hourglassUP = false;
	hourglassGet = false;
	clockUP = false;
	clockGet = false;
	doorOpen = false;
	bMenu = false;
	godmode = false;
	time = 99;
	ScreenPosY = SCREEN_HEIGHT+2;
	sound.stopBGM();

	skeletons.clear();
	vampires.clear();
	ghosts.clear();


	level_scene = level;
		switch (level_scene)
		{
		case 0:
			initMenu();
			bMenu = true;
			bLost = false;
			bWin = false;
			hp = 3;
			map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y - 32), texProgram);
			break;
		case 1:
			map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y - 32), texProgram);
			sound.ChangeVolum(0.3);
			sound.playBGM("audio/Fungal Funk.mp3", true);
			break;
		case 2:
			map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y - 32), texProgram);
			sound.ChangeVolum(0.3);
			sound.playBGM("audio/Rhythmortis.mp3", true);
			break;
		case 3:
			map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y - 32), texProgram);
			sound.ChangeVolum(0.3);
			sound.playBGM("audio/Crypteque.mp3", true);
			break;
		default:
			break;
		}

	int tileSize = map->getTileSize();
	int len = map->enemies.size();
	
	for (int i = 0; i < len; ++i) {
		if (map->enemies[i].enemyType == 's') {
			skeleton = new Skeleton();
			skeleton->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			skeleton->setPosition(glm::vec2(map->enemies[i].pos.x * map->getTileSize(), map->enemies[i].pos.y * map->getTileSize() - 11));
			skeleton->setTileMap(map);
			skeletons.push_back(skeleton);
		}
		else if (map->enemies[i].enemyType == 'v') {
			vampire = new Vampire();
			vampire->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			vampire->setPosition(glm::vec2(map->enemies[i].pos.x * map->getTileSize(), map->enemies[i].pos.y * map->getTileSize() - 18));
			vampire->setTileMap(map);
			vampires.push_back(vampire);
		}
		else if (map->enemies[i].enemyType == 'g') {
			ghost = new Ghost();
			ghost->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ghost->setPosition(glm::vec2(map->enemies[i].pos.x * map->getTileSize(), map->enemies[i].pos.y * map->getTileSize() - 18));
			ghost->setTileMap(map);
			ghosts.push_back(ghost);
		}
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


	Healthsheet.loadFromFile("images/health.png", TEXTURE_PIXEL_FORMAT_RGBA);
	health = Sprite::createSprite(glm::ivec2(20,18), glm::vec2(1, 1), &Healthsheet, &texProgram);
	health->setNumberAnimations(1);
	health->setAnimationSpeed(0, 8);
	health->addKeyframe(0, glm::vec2(0.f, 0.f));
	health->changeAnimation(0);

	//Creando los sprites de los numeros a partir del spritesheet
	
	Numbersheet.loadFromFile("images/NumberFont.png", TEXTURE_PIXEL_FORMAT_RGBA);
	numbers = Sprite::createSprite(glm::ivec2(23, 30), glm::vec2(0.1, 1), &Numbersheet, &texProgram);
	numbers->setNumberAnimations(10);
	for (int i = 0; i < 10; i++) {

		numbers->setAnimationSpeed(i, 0);
		numbers->addKeyframe(i, glm::vec2(i*.1f, 0.f));

	}
	numbers->changeAnimation(9);

	Levelsheet.loadFromFile("images/nivel.png", TEXTURE_PIXEL_FORMAT_RGBA);
	nivel = Sprite::createSprite(glm::ivec2(87, 30), glm::vec2(1, 1), &Levelsheet, &texProgram);
	nivel->setNumberAnimations(1);
	nivel->setAnimationSpeed(0, 0);
	nivel->addKeyframe(0, glm::vec2(0.f, 0.f));
	nivel->changeAnimation(0);

	//inicializando los vectores de sprites de tiempo y puntuación
	
	Timevec.push_back(*numbers);
	Timevec.push_back(*numbers);
	numbers->changeAnimation(0);
	Pointvec.push_back(*numbers);
	Pointvec.push_back(*numbers);
	Pointvec.push_back(*numbers);
	Pointvec.push_back(*numbers);
	Pointvec.push_back(*numbers);



	maxblock = map->getNblock();

	texWin.loadFromFile("images/win.png", TEXTURE_PIXEL_FORMAT_RGBA);
	winScreen = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &texWin, &texProgram);

	texLost.loadFromFile("images/gameover.png", TEXTURE_PIXEL_FORMAT_RGBA);
	gameover = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &texLost, &texProgram);

	door = new Item();
	door -> door_init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
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

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}


void Scene::update(int deltaTime)
{

	if (bMenu) {
		menu->update(deltaTime);
	}
	else if (bWin) 
	{
		if (ScreenPosY > 0)
			ScreenPosY = ScreenPosY - float(0.25f * deltaTime);
		else {
			if (Game::instance().getKey(13)) {
				init(0);
			}
		}
		winScreen->setPosition(glm::vec2(0.0f, ScreenPosY));
	}

	else if (bLost) {
		if (ScreenPosY > 0)
			ScreenPosY = ScreenPosY - float(0.2f * deltaTime);
		else {
			if (Game::instance().getKey(13)) {
				init(0);
			}
		}
		gameover->setPosition(glm::vec2(0.0f, ScreenPosY));
	}
	else if(delay_start >= 50) 
	{
		//Jump Level & godmode
		if (Game::instance().getKey('g')) {
			godmode = !godmode;
		}
		else if (Game::instance().getKey('1')) {
			init(1);
		}
		else if (Game::instance().getKey('2')) {
			init(2);
		}
		else if (Game::instance().getKey('3')) {
			init(3);
		}
		else if (Game::instance().getKey('k')) {
			keyUP = true;
		}

		//timer logic
		if (timer <= 0) {
			time--;
			timer = 60;

		}
		if (time < 9) {
			Timevec[0].changeAnimation(time);
			Timevec[1].changeAnimation(0);
		}
		else if (time == 0 && !keyGet) bLost = true;
		else {
			Timevec[0].changeAnimation(time % 10);
			Timevec[1].changeAnimation(time / 10);
		}

		

		//Check HP
		if (hp == 0) {
			sound.stopBGM();
			sound.ChangeVolum(0.4);
			sound.playBGM("audio/lost.mp3", false);
			bLost = true;
		}

		currentTime += deltaTime;
		player->update(deltaTime);
		if (invencibility > 0) invencibility--;
		if (keyGet ||  hourglassGet and currentTime - actual_time <= 4000) { // TIME STOP 

		}
		else {

			timer--;

			if (hourglassGet and currentTime - actual_time >= 4000) {
				sound.ChangeVolum(1.0);
				sound.resumeBGM();
			}
			for (int i = 0; i < skeletons.size(); ++i) {

				if (invencibility <= 0 and skeletons[i]->isColliding(player->getposPlayer()) and not godmode) {
					sound.playSFX("sounds/lose_life.mp3");
					hp--;
					invencibility = 60;
				}
				skeletons[i]->update(deltaTime);
			}

			for (int i = 0; i < vampires.size(); ++i) 
			{

				if (invencibility <= 0 and vampires[i]->isColliding(player->getposPlayer()) and not godmode) {
					player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
					sound.playSFX("sounds/lose_life.mp3");
					hp--;
					invencibility = 60;
				}
				vampires[i]->update(deltaTime);
			}
			for (int i = 0; i < ghosts.size(); ++i) {
				if (invencibility <= 0 and ghosts[i]->isColliding(player->getposPlayer()) and not godmode) {
					player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
					sound.playSFX("sounds/lose_life.mp3");
					hp--;
					invencibility = 60;
				}
				ghosts[i]->update(deltaTime);

			}

		}
		points = puntuation + 50 * (-map->getNblock() + maxblock);

		int temp = points;
		for (int i = 0; i < 5; ++i) {	
			if (temp >= 0)
				Pointvec[i].changeAnimation(temp % 10);
			temp = temp / 10;
		}
		// decision when produce a collision with door 
		switch (level_scene)
		{
		case 1:
			if (door->collisionItem(player->getposPlayer()) && keyGet) {
				puntuation += 50*maxblock+1000;
				
				if (time ==  0) init(2);
				else {
					time--;
					puntuation += 20;

				}
			}
			break;
		case 2:
			if (door->collisionItem(player->getposPlayer()) && keyGet) {
				puntuation += 50*maxblock+1000;
				init(3);
			}
			break;
		case 3:
			if (door->collisionItem(player->getposPlayer()) && keyGet) {
				bWin = true;
				sound.stopBGM();
				sound.ChangeVolum(0.4);
				sound.playBGM("audio/win.mp3", false);
			}
			break;
		default:
			break;
		}


		if (invencibility <= 0 and map->collisionTrap(player->getposPlayer(), glm::ivec2(32, 32))) {
			player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
			hp--;
			sound.playSFX("sounds/lose_life.mp3");
			invencibility = 60;
		}

		for (int i = 0; i < items.size(); ++i) {
			switch (i)
			{
			case 0: //COIN
				if (items[0]->collisionItem(player->getposPlayer()) && not coinGet && coinUP) {
					coinGet = true;
					sound.playSFX("sounds/coin.mp3");
					puntuation += 1000;
				}
				items[0]->update(deltaTime);

			case 1: // KEY

				if (items[1]->collisionItem(player->getposPlayer()) && keyUP && not keyGet) {
					sound.playSFX("sounds/key.mp3");
					keyGet = true;
					doorOpen = true;
					door->doorOpen();
					door->update(deltaTime);
				}
				items[1]->update(deltaTime);

			case 2: // HOURGLASS
				if (items[2]->collisionItem(player->getposPlayer()) && not hourglassGet && hourglassUP) {
					hourglassGet = true;
					sound.pauseBGM();
					sound.ChangeVolum(0.15);
					sound.playSFX("sfx/zawarudo.wav");
					actual_time = currentTime;
				}
				items[2]->update(deltaTime);

			case 3: // CLOCK
				if (items[3]->collisionItem(player->getposPlayer()) && not clockGet && clockUP) {
					clockGet = true;
					time += 10;
					sound.playSFX("sounds/clock.mp3");
				}
				items[3]->update(deltaTime);

			default:
				break;
			}
		}
	}
	else {
		++delay_start;
	}


	

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

	if (not bMenu) {

		backgound->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));
		backgound->render();
		map->render();
		door->render();

		for (int i = 0; i < hp; ++i) {
			health->setPosition(glm::vec2(6+(i * 22), 6));
			health->render();
		}

		if (not keyGet) {
			if (map->getNblock() == 0) {
				keyUP = true;
			}
			if (keyUP) {
				items[1]->render();
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

		if (currentTime >= 10000 and not clockGet) { // Hourglass
			items[3]->render();
			clockUP = true;
		}

		if (invencibility <= 0) player->render();
		else if (invencibility % 10 > 5) player->render();
		 

		

		for (int i = 0; i < 5; ++i) {

			Pointvec[i].setPosition(glm::vec2(225 - i * 25, 2));
			Pointvec[i].render();
			
			

		}

		Timevec[1].setPosition(glm::vec2(500, 2));
		Timevec[1].render();
		Timevec[0].setPosition(glm::vec2(527, 2));
		Timevec[0].render();

		
		
		nivel->setPosition(glm::vec2(270, 2));
		nivel->render();
		numbers->setPosition(glm::vec2(360, 2));
		numbers->changeAnimation(level_scene);
		numbers->render();


		int tileSize = map->getTileSize();


		vector<glm::ivec2> positionBlock = map->getpositionBlock();
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

		int len = skeletons.size();
		for (int i = 0; i < len; i++) {
			skeletons[i]->render();
		}
		for (int i = 0; i < vampires.size(); i++) {
			vampires[i]->render();
		}
		for (int i = 0; i < ghosts.size(); i++) {
			ghosts[i]->render();
		}

		if (bWin) {
			winScreen->render();
		}
		if (bLost) {
			gameover->render();
		}
	}
	else menu->render();
	
}

void Scene::showscene()
{
	init(1);
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

void Scene::initMenu() {
	menu = new Menu();
	menu->init(texProgram);
	sound.ChangeVolum(0.6);
	sound.playBGM("audio/Ori and the Blind Forest.mp3",false);
}


