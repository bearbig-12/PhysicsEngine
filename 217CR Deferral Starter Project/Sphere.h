#pragma once

#include "GameObject.h"

//A basic sphere class derived from a game object
//It can move (basic position changing only at the moment!) via the arrow keys
class Sphere : public GameObject
{
public:
	// -- variables --
	float radius;
	Vec3 Sphere_velocity;
	float mass;
	// -- constructors/destructors --
	Sphere(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - radius 1 - move speed - 1)
	Sphere(float _x, float _y, float _z, float _radius);
	Sphere(float _x, float _y, float _z, 
		   float _r, float _g, float _b, 
		   float _radius); //pass in a position, colour and radius
	Sphere(float _x, float _y, float _z,
		float _r, float _g, float _b,
		float _radius,float _mass); //pass in a position, colour, radius and mass
	~Sphere() {}; //default destructor

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};