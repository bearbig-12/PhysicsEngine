#include "Cube.h"

//We can either hard code the values in GameObject (like in Cube())
//or
//We can use the GameEngine constructors to fill the values ( like in Cube(x, y, z, size))
Cube::Cube()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	r = 1.0f;
	g = 0.0f;
	b = 1.0f;

	size = 1.0f;

	velocity = Vec3(0, 0, 0);
}

Cube::Cube(float _x, float _y, float _z, float _size)
	:GameObject(_x, _y, _z) //note the use of GameObject constructor
{
	size = _size;
	velocity = Vec3(0, 0, 0);
}

Cube::Cube(float _x, float _y, float _z, 
		   float _r, float _g, float _b, 
		   float _size):
	GameObject(_x, _y, _z, _r, _g, _b) //note the use of GameObject constructor
{
	size = _size;
	velocity = Vec3(0, 0, 0);
}

//Position and colour a cube in the scene
void Cube::Draw()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glColor3f(r, g, b);
		glutSolidCube(size);
		//glutWireCube(size) - if you'd rather see through it
	glPopMatrix();
}

void Cube::Update(float deltaTime)
{
	//Cubes are static at the moment so nothing changes for them
}
