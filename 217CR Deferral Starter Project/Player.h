#pragma once
#include "GameObject.h"
#include "Vec3.h"
#include <vector>
#include "Sphere.h"
#include "Bullet.h"
#include <iostream>
class Player :
    public GameObject
{
public:
    float size;
	//float MoveSpeed;
	float mMass;

	// For Linear motion
	Vec3 mAcceleration;
	Vec3 mVelocity;
	Vec3 mTotalForce;
	Vec3 mPosition;
	//For Angular motion
	Vec3 mR_acceleration; 
	Vec3 mR_velocity;
	Vec3 mR_force; // torque
	float mR_orientation;
	float mR_inertia;		//Moment of Inertia
	

	Vec3 Heading_Vec;
	
	
	static int Jump_time; // For player's jump delay

	

	Player();
	Player(float _x, float _y, float _z, float _size, float _mass,  float inertia);  //pass in a position, size, mass and MOI
	Player(float _x, float _y, float _z, float _r, float _g, float _b, float _size, float _mass); //pass in a position, colour, size and mass.
	~Player() {}; //default destructor
	
	

public:
	void CalculateForces();

	virtual void Draw();
	virtual void Update(float deltatime);
	
};


