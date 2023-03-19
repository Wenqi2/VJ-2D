#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void update_map(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture Blocsheet;
	Texture Keysheet;
	Texture Doorsheet;
	Texture Coinsheet;
	Sprite* block2;
	Sprite* key;
	Sprite* door;
	Sprite* coin;
	bool Bkey = true;
	bool doorOpen = false;
};


#endif // _SCENE_INCLUDE

