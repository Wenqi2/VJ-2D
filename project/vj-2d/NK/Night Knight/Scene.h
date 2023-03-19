#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>

#include "Skeleton.h"




// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void update_map(int deltaTime);
	

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
	Texture Fruitsheet;
	Sprite* block2;
	Sprite* key;
	Sprite* door;
	Sprite* Fruit;
	bool Bkey = true;

	Skeleton *skeleton;
	vector <Skeleton*> skeletons;
	

};

#endif


