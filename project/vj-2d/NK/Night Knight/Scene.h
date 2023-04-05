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

	void init(int level);
	void initMenu();
	void update(int deltaTime);
	void render();
	void showscene();
	

private:
	void initShaders();

private:
	SoundManager sound;
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

	Texture texWin;
	Sprite* winScreen;
	Texture texLost;
	Sprite* gameover;

	Texture Doorsheet;

	Texture Numbersheet;
	Sprite* numbers;
	int puntuation = 0;
	int points = 0;
	int maxblock = 0;
	int time = 0;
	int timer = 60;
	vector <Sprite> Timevec;
	vector <Sprite> Pointvec;


	bool keyUP = false;
	bool keyGet = false;
	bool coinUP = false;
	bool coinGet = false;
	bool hourglassUP = false;
	bool hourglassGet = false;
	bool clockUP = false;
	bool clockGet = false;
	bool doorOpen = false;
	bool godmode;
	bool bMenu ;
	bool bLost;
	bool bWin;
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
	int level_scene;
	int delay_start;
	int ScreenPosY;
	
};

#endif


