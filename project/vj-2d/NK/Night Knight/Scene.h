#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>

#include "Ghost.h"
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

	Texture Doorsheet;

	bool keyUP = false;
	bool keyGet = false;
	bool coinUP = false;
	bool coinGet = false;
	bool hourglassUP = false;
	bool hourglassGet = false;
	bool clockUP = false;
	bool clockGet = false;
	bool doorOpen = false;

	Skeleton *skeleton;
	Vampire *vampire;
	Ghost* ghost;
	vector <Skeleton*> skeletons;
	vector <Vampire*> vampires;
	vector <Ghost*> ghosts;
	Item* coin;
	Item* key;
	Item* hourglass;
	Item* clock;
	Item* door;
	vector<Item*> items;
	int actual_time = 0;
	
};

#endif


