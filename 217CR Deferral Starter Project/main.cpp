
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GameObject.h"
#include "GameEngine.h"

#pragma comment(lib, "glew32.lib") 


using namespace std;

// Collider Type CUBE = 0, SPHERE = 1

GameObject* player = new Player(0.0f, -4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
GameObject* cube_collider = new ColliderCube(1.0f, player, 0);	// size , object, collider_type

GameObject* target = new Sphere(-2.0f, 3.0f, 0, 1.0f, 0, 0, 0.5f,  10.0f); // x, y, z, r, g, b, radius and mass
GameObject* target_collider = new CollidierSphere(0.5f, target, 1);

GameObject* target_second = new Sphere(5.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 50.0f);
GameObject* target_collider_second = new CollidierSphere( 1.0f, target_second, 1);

GameObject* target_third = new Sphere(2.0f, 0.0f, 3.0f, 1.0f, 0.0f, 0.0f, 0.50f, 10.0f);
GameObject* target_collider_third = new CollidierSphere(0.5f, target_third, 1);

GameObject* target_forth = new Sphere(3.0f, -4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.50f, 10.0f);
GameObject* target_collider_forth = new CollidierSphere(0.5f, target_forth, 1);


GameObject* cubeTarget = new Cube(-4.0f, -4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
GameObject* cube_collider_second = new ColliderCube(1.0f, cubeTarget, 0); // size , object, collider_type

GameObject* cubeTarget2 = new Cube(0.0f, -0.0f, 5.0f, 1.0f, 0.0f, 0.0f, 1.0f); // x, y, z, r, g, b and size
GameObject* cube_collider_third = new ColliderCube(1.0f, cubeTarget2, 0);

GameObject* wall = new Cube(0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 10.0f);
GameObject* wall_collider = new ColliderCube(10.0f, wall, 2);

GameEngine engine;

//Entry point into the program
int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "Leo's Project", 500, 500);
	

	engine.AddGameObject(player);
	engine.AddObjects_Collider(cube_collider);

	engine.AddGameObject(target);
	engine.AddObjects_Collider(target_collider);

	engine.AddGameObject(target_second);
	engine.AddObjects_Collider(target_collider_second);

	engine.AddGameObject(target_third);
	engine.AddObjects_Collider(target_collider_third);

	engine.AddGameObject(target_forth);
	engine.AddObjects_Collider(target_collider_forth);

	engine.AddGameObject(cubeTarget);
	engine.AddObjects_Collider(cube_collider_second);

	engine.AddGameObject(cubeTarget2);
	engine.AddObjects_Collider(cube_collider_third);

	engine.AddGameObject(wall);
	engine.AddObjects_Collider(wall_collider);

	engine.StartEngine();

	return 0;
	//It was not easy to do but Ian and DrWill helped me alot so I could make this. 
	//If I were alone, I would never have been able to complete this. 
	//I'm really grateful to them.
}