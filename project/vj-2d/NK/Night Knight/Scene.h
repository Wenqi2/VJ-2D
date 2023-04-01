#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>

#include "Ghost.h"
#include "Item.h"
#include "Menu.h"




// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void initMenu();
	void update(int deltaTime);
	void render();
	void showscene();
	

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
	Texture Healthsheet;
	Sprite* health;

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

	bool bMenu = true;
	Menu* menu;


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
	int hp = 3;
	int invencibility = 0;
	
};

#endif


