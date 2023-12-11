#pragma once
#include "Player.h"
class Bullet : public GameObject
{
	public:
		float r;
		float g;
		float b;

		float bullet_radius;
		Vec3 bullet_Velocity;
		
		float speed = 5.0f;
		Vec3 bullet_Position;
		Vec3 bullet_Heading_Vec;
		float bullet_mass;

		Bullet(GameObject* _player); // Need to bind bullet obj with player obj.
		~Bullet() {};

		virtual void Draw();
		virtual void Update(float deltaTime);
};

