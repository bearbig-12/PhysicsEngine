#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Sphere.h"
class CollidierSphere :
    public GameObject
{
public:
    Vec3 Collider_position;
    float Collider_radius;
    GameObject* Sphere_object;

    

public:
    CollidierSphere(float _x, float _y, float _z, float raidus, GameObject* bind_sphere);
    CollidierSphere(float raidus, GameObject* bind_sphere, int type);
   

    bool Sphere_SphereCheck(GameObject* other);

    void PrintData();
    virtual void Draw();
    virtual void Update(float deltaTime);
};

