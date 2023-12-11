#include "CollidierSphere.h"

CollidierSphere::CollidierSphere(float _x, float _y, float _z, float raidus, GameObject* bind_sphere)
{
	
	Sphere_object = bind_sphere;

	x = _x;
	y = _y;
	z = _z;

	Collider_radius = raidus;

	mType = 1;	// 1 is for Collider type. Sphere is 1 and Cube is 0
}

CollidierSphere::CollidierSphere(float raidus, GameObject* bind_sphere, int type)
	
{
	Sphere_object = bind_sphere;

	x = Sphere_object->x;
	y = Sphere_object->y;
	z = Sphere_object->z;

	Collider_radius = raidus;

	mType = type;
}





void CollidierSphere::Draw()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(r, g, b);
	//glutSolidSphere(radius, 10, 10); //if you'd rather it shows solid
	glutWireSphere(Collider_radius, 10, 10);
	glPopMatrix();
}

void CollidierSphere::PrintData() {
	std::cout << "(" << Collider_position.x << "," << Collider_position.y << "," << Collider_position.z << ")" << "Radius:" << Collider_radius << std::endl;

}

bool CollidierSphere::Sphere_SphereCheck(GameObject* _other)
{
	
	CollidierSphere* other = (CollidierSphere*)_other;
	//PrintData();
	//other->PrintData();

	Vec3 temp = Vec3(this->x - other->x, this->y - other->y, this->z - other->z); 
	// Need to know distance from A sphere collider's centre to B's centre
	float distance = Magnitude(temp);	
	//std::cout << "distance" << distance << std::endl;

	float Sum_Radius = this->Collider_radius + other->Collider_radius;

	if (distance <= Sum_Radius)
	{
		return true;
	}
	return false;
	
	
}

void CollidierSphere::Update(float deltaTime)
{
	x = Sphere_object->x;
	y = Sphere_object->y;
	z = Sphere_object->z;
	
}
