#pragma once

#include "GameObject.h"

//A basic cube class derived from a game object
class Cube: public GameObject
{
public:
	// -- variables --
	float size;
	Vec3 velocity;
	// -- constructors/destructors --
	Cube(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	Cube(float _x, float _y, float _z, float _size);  //pass in a position and size
	Cube(float _x, float _y, float _z, 
		 float _r, float _g, float _b, 
		 float _size); //pass in a position, colour and size
	~Cube() {}; //default destructor

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};