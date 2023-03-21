#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>

#include "Skeleton.h"
#include "Item.h"




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
	

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture Blocsheet;
	Sprite* block2;
	Texture Trapsheet;
	Sprite* trap;
	Texture Backsheet;
	Sprite* backgound;

	bool Bkey = true;

	Skeleton *skeleton;
	vector <Skeleton*> skeletons;
	Item* item;
	

	bool doorOpen = false;
};

#endif


