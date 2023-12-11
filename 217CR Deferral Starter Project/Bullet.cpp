#include "Bullet.h"

Bullet::Bullet(GameObject* _player)
{
	

	//bullet_Position.x = 0;
	//bullet_Position.y = 0;
	//bullet_Position.z = 0;

	r = 0.0f;
	g = 0.0f;
	b = 1.0f;

	bullet_radius = 0.1f;
	Player* temp = (Player*)_player;				
	bullet_Velocity = temp->Heading_Vec*speed;		
	//bullet_Heading_Vec = temp->Heading_Vec;
	bullet_Position = temp->mPosition;

	x = temp->mPosition.x;
	y = temp->mPosition.y;
	z = temp->mPosition.z;

	bullet_mass = 0.01f;
}

void Bullet::Draw()
{
	glPushMatrix();
	glTranslatef(x, y, z );
	glColor3f(r, g, b);
	glutSolidSphere(bullet_radius, 10, 10); //if you'd rather it shows solid
	//glutWireSphere(bullet_radius, 10, 10);
	glPopMatrix();
}

void Bullet::Update(float deltaTime)
{	
	
	//bullet_Position += bullet_Velocity * deltaTime;

	x += bullet_Velocity.x * deltaTime;
	y += bullet_Velocity.y * deltaTime;
	z += bullet_Velocity.z * deltaTime;
	//std::cout << bullet_Position.x << "," << bullet_Position.y << "," << bullet_Position.z << std::endl;
	
	bullet_Velocity *= pow(0.9f, deltaTime);
}
