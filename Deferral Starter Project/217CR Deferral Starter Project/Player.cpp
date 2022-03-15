#include "Player.h"
#include <iostream>

int Player::Jump_time = 0;
Player::Player()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	r = 1.0f;
	g = 0.0f;
	b = 1.0f;

	size = 1.0f;
	//MoveSpeed = 5.0f;

	Heading_Vec = Vec3(0, 1, 0);
}

Player::Player(float _x, float _y, float _z, float _size, float _mass,float _inertia) : GameObject(_x, _y, _z) //xyz, size
{
	size = _size;
	mMass = _mass;
	//MoveSpeed = _movespeed;

	mVelocity = Vec3(0, 0, 0);
	mAcceleration = Vec3(0, 0, 0);
	mTotalForce = Vec3(0, 0, 0);
	mPosition = Vec3(_x, _y, _z);

	mR_acceleration = Vec3(0, 0, 0);
	mR_velocity = Vec3(0, 0, 0);
	mR_force = Vec3(0, 0, 0);
	mR_orientation = 0.0f;
	mR_inertia = _inertia;

	Heading_Vec = Vec3(0, 1, 0);
}

Player::Player(float _x, float _y, float _z, 
	float _r, float _g, float _b, float _size, float _mass) // xyz , size and colour
	: GameObject(_x, _y, _z, _r, _g, _b)
{
	size = _size;
	//MoveSpeed = _movespeed;
	mMass = _mass;

	mVelocity = Vec3(0, 0, 0);
	mAcceleration = Vec3(0, 0, 0);
	mTotalForce = Vec3(0, 0, 0);
	mPosition = Vec3(_x, _y, _z);

	mR_acceleration = Vec3(0, 0, 0);
	mR_velocity = Vec3(0, 0, 0);
	mR_force = Vec3(0, 0, 0);
	mR_orientation = 0.0f;
	mR_inertia = (mMass * (_size * _size + _size * _size)) / 12;	// player is Cube
	// Moment of inertia 

	Heading_Vec = Vec3(0, 1, 0);

	
	
}



void Player::CalculateForces()	
{
	// To make a force 0. If I do not do this, the force it keep adding so the obj move too fast
	Normalization(Heading_Vec);
	mR_force = Vec3(0, 0, 0);
	mTotalForce = Vec3(0, 0, 0);

	if (this->mPosition.z > 0)	// gravity
	{
		mTotalForce.z += -9.8f * mMass;
	}
	else
	{
		mVelocity.z = 0;
	}
	
}

void Player::Draw()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex3f(mPosition.x, mPosition.y, mPosition.z);
	glVertex3f(x, y,z);
	//glVertex3f(Heading_Vec.x + mPosition.x, Heading_Vec.y + mPosition.y, Heading_Vec.z + mPosition.z);
	glVertex3f(Heading_Vec.x + x, Heading_Vec.y +y, Heading_Vec.z + z);
	glEnd();

	
	glTranslatef(x, y, z);
	glRotatef(mR_orientation, 0, 0, 1); // For rotating player object
	glColor3f(r, g, b);


	float radian = Radian(mR_orientation); // Turn Degree into Radian
	float z_Axis[3][3] = {					// Rotate matirx for z axis
		{cos(radian), -sin(radian), 0},
		{sin(radian), cos(radian), 0},
		{0,0,1}
	};
	

	Heading_Vec = MatCalculate(z_Axis, Vec3(0, 1, 0));	// To rotate the Heading vector.
	//update the orientation, also rotate the heading by that much too so its always facing forward.
	glutWireCube(size);
	

	glPointSize(10.0f); // so we can see the point better

	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_POINTS);
	//at the middle of object
	glVertex3f(0, 0, 0);
	glEnd();

	glPopMatrix();
}

void Player::Update(float deltaTime)
{
	
	CalculateForces();

	if (GameObject::keys['w'] == true)
		mTotalForce += Heading_Vec;
	if (GameObject::keys['s'] == true)
		mTotalForce -= Heading_Vec;

	if (GameObject::keys[' '] == true)
	{
		int current = glutGet(GLUT_ELAPSED_TIME);
		if(current - Jump_time > 2000 && this->mPosition.z <= 0)	// 2 seconds delay for next  jumping
		{
			
			Jump_time = current;
			mTotalForce.z += 2000.0f;
		}
	}
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		mR_force -= Cross(Vec3(0.5, 0.5, 0), Vec3(10, 0, 0));
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		mR_force += Cross(Vec3(-0.5, 0.5, 0), Vec3(10, 0, 0));
	//Torque = Force * displacement(The shortest distance between the two points = Cross product)
	//mR_force = Torque
	
	//semi implicit euler function
	mAcceleration = mTotalForce / mMass;

	mVelocity = mVelocity + mAcceleration * deltaTime;
	//mVelocity += mAcceleration * deltaTime;
	
	mPosition = mPosition + mVelocity * deltaTime;

	x = mPosition.x;
	y = mPosition.y;
	z = mPosition.z;
	//mPosition += mVelocity * deltaTime;
	

	//mVelocity = mVelocity * pow(0.5, deltaTime); // for damping
	mVelocity *= pow(0.5f, deltaTime);

	/*x = mPosition.x + mVelocity.x * deltaTime;
	y = mPosition.y + mVelocity.y * deltaTime;
	z = mPosition.z + mVelocity.z * deltaTime;*/
	
	//Torque (Angular Motion)
	float mat_Inertia[3][3]	// moment of inertia matrix 
	{
		{mR_inertia, 0, 0},
		{0, mR_inertia, 0},
		{0, 0, mR_inertia}
	};
	mR_acceleration = MatInverse(mat_Inertia, mR_force);
	//mR_acceleration = Torque / Moment of inertia;
	//mR_force = Torque

	mR_velocity = mR_velocity + mR_acceleration * deltaTime;

	mR_orientation = mR_orientation + mR_velocity.z * deltaTime;

	mR_velocity *= pow(0.5f, deltaTime);


}
