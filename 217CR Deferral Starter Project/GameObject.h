#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Vec3.h"
#include <map>

//A basic abstract class that all game objects in the scene are based off
// abstract = We never will make a direct instance of GameObject but will make classes inherit from it
class GameObject
{
public:
	// -- variables --
	float x, y, z; //position
	
	float r, g, b; //colour

	int mType;	// Cube_Collider = 0 , Sphere is 1, wall is 2
	
	static std::map<char, bool> keys; //save key presses and let game objects access them
	static std::map<int, bool> specialKeys; //static = one instance of these variables for the whole class (top of .cpp)
	
	// -- constructors/destructors --
	GameObject(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta)
	GameObject(float _x, float _y, float _z); //pass in a position (no colour passed in so defaults to white)

	

	GameObject(float _x, float _y, float _z, 
		float _r, float _g, float _b); //pass in a position, colour

	

	~GameObject(); //default destructor

	// -- functions -- 
	//pure virtual so all classes that derive from this one need to include a definion for these
	virtual void Draw() = 0; 
	virtual void Update(float deltaTime) = 0;
	
};