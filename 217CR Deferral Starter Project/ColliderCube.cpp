#include "ColliderCube.h"

ColliderCube::ColliderCube(float _x, float _y, float _z, float _size, GameObject* bind_cube)
{
	Cube_object = bind_cube;
	
	x = _x;
	y = _y;
	z = _z;

	Cube_Collider_Size = _size;

	mType = 0;
}

ColliderCube::ColliderCube(float _size, GameObject* bind_cube, int type)
	
{
	Cube_object = bind_cube;

	x = Cube_object->x;
	y = Cube_object->y;
	z = Cube_object->x;

	Cube_Collider_Size = _size;

	mType = type;
}



void ColliderCube::PrintData()
{
	std::cout << " Max : " << Max.x << ", " << Max.y << ", " << Max.z << ", " << std::endl;
	std::cout << " Min : " << Min.x << ", " << Min.y << ", " << Min.z << ", " << std::endl;
}

void ColliderCube::Draw()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(r, g, b);
	//glutSolidCube(Cube_Collider_Size);
	glutWireCube(Cube_Collider_Size);
	glPopMatrix();
}

bool ColliderCube::AABB_AABB(GameObject* _other)
{
	ColliderCube* other = (ColliderCube*)_other;
	//PrintData();
	//other->PrintData();
	this->Max = Vec3(
		this->x + this->Cube_Collider_Size / 2.0f,
		this->y + this->Cube_Collider_Size / 2.0f,
		this->z + this->Cube_Collider_Size / 2.0f);
	this->Min = Vec3(
		this->x - this->Cube_Collider_Size / 2.0f,
		this->y - this->Cube_Collider_Size / 2.0f,
		this->z - this->Cube_Collider_Size / 2.0f);

	other->Max = Vec3(
		other->x + other->Cube_Collider_Size / 2.0f,
		other->y + other->Cube_Collider_Size / 2.0f,
		other->z + other->Cube_Collider_Size / 2.0f);
	other->Min = Vec3(
		other->x - other->Cube_Collider_Size / 2.0f,
		other->y - other->Cube_Collider_Size / 2.0f,
		other->z - other->Cube_Collider_Size / 2.0f);

	if (this->Max.x > other->Min.x && this->Min.x < other->Max.x &&
		this->Max.y > other->Min.y && this->Min.y < other->Max.y && 
		this->Max.z > other->Min.z && this->Min.z < other->Max.z)
	{
		return true;
	}


	return false;
}

bool ColliderCube::AABB_Sphere(GameObject* _sphere)
{
	CollidierSphere* sphere = (CollidierSphere*)_sphere;

	this->Max = Vec3(
		this->x + this->Cube_Collider_Size / 2.0f,
		this->y + this->Cube_Collider_Size / 2.0f,
		this->z + this->Cube_Collider_Size / 2.0f);
	this->Min = Vec3(
		this->x - this->Cube_Collider_Size / 2.0f,
		this->y - this->Cube_Collider_Size / 2.0f,
		this->z - this->Cube_Collider_Size / 2.0f);

	Vec3 Close_point;
	if (sphere->x < this->Min.x)
	{
		Close_point.x = Min.x;
	}
	else if (sphere->x > this->Max.x)
	{
		Close_point.x = Max.x;
	}
	else
	{
		Close_point.x = this->x;
	}

	if (sphere->y < this->Min.y)
	{
		Close_point.y = this->Min.y;
	}
	else if (sphere->y > this->Max.y)
	{
		Close_point.y = this->Max.y;
	}
	else
	{
		Close_point.y = this->y;
	}

	if (sphere->z < this->Min.z)
	{
		Close_point.z = this->Min.z;
	}
	else if (sphere->z > this->Max.z)
	{
		Close_point.z = this->Max.z;
	}
	else
	{
		Close_point.z = this->z;

	}

	Vec3 temp = Vec3(sphere->x - Close_point.x, sphere->y - Close_point.y, sphere->z - Close_point.z);
	float distance = Magnitude(temp);

	if (distance < sphere->Collider_radius)
	{
		return true;
	}

	return false;
}

void ColliderCube::Update(float deltaTime)
{
	x = Cube_object->x;
	y = Cube_object->y;
	z = Cube_object->z;
}

