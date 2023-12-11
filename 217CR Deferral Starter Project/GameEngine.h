#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector>
#include <list>
#include <iostream>

#include "GameObject.h"
#include "Vec3.h"
#include "Cube.h"
#include "Sphere.h"
#include "Player.h"
#include "Bullet.h"
#include "CollidierSphere.h"
#include "ColliderCube.h"


class GameEngine
{
private:
	static std::vector<GameObject*> objects;
	static std::vector<GameObject*> objects_collider;



	static int oldTimeSinceStart;
	static int newTimeSinceStart;
	static int LastShot; // For shooting delay.
	static int Score;
	static int HP;
	//static int bullet_count;

private:
	static void UpdateGame(void);
	static void DrawGame(void);
	static void CleanUpEngine(void);

	static void ResizeWindow(int w, int h);

	static void keyInput(unsigned char key, int x, int y);
	static void keyInputUp(unsigned char key, int x, int y);

	static void keySpecialInput(int key, int x, int y);
	static void keySpecialInputUp(int key, int x, int y);

	
public:
	void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height);
	static void AddGameObject(GameObject* object);
	static void AddObjects_Collider(GameObject* obj_collider);

	void StartEngine();
};

