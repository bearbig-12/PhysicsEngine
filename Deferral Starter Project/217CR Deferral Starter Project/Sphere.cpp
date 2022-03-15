#include "Sphere.h"

//We can either hard code the values in GameObject (like in Sphere())
//or
//We can use the GameEngine constructors to fill the values ( like in Sphere(x, y, z, radius, speed))
Sphere::Sphere()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	r = 1.0f;
	g = 0.0f;
	b = 1.0f;

	radius = 1.0f;
	Sphere_velocity = Vec3(0, 0, 0);
	mass = 1;
}

Sphere::Sphere(float _x, float _y, float _z, float _radius)
	:GameObject(_x, _y, _z) //note the use of GameObject constructor
{
	radius = _radius;
	Sphere_velocity = Vec3(0, 0, 0);
	mass = 1;
}

Sphere::Sphere(float _x, float _y, float _z,
			   float _r, float _g, float _b,
			   float _radius):
	GameObject(_x, _y, _z, _r, _g, _b) //note the use of GameObject constructor
{
	radius = _radius;
	Sphere_velocity = Vec3(0, 0, 0);
	mass = 1;
}

Sphere::Sphere(float _x, float _y, float _z, 
			   float _r, float _g, float _b, 
			   float _radius,float _mass):
	GameObject(_x, _y, _z, _r, _g, _b)
{
	radius = _radius;
	Sphere_velocity = Vec3(0, 0, 0);
	mass = _mass;
}

void Sphere::Draw()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glColor3f(r, g, b);
		glutSolidSphere(radius, 10, 10); //if you'd rather it shows solid
		//glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

void Sphere::Update(float deltaTime)
{
	x += Sphere_velocity.x;
	y += Sphere_velocity.y;
	z += Sphere_velocity.z;

	Sphere_velocity *= pow(0.5f, deltaTime);

}
