#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Cube.h"
#include <iostream>
#include "CollidierSphere.h"
class ColliderCube :
    public GameObject
{
public:
   
    float Cube_Collider_Size;
    GameObject* Cube_object;
    Vec3 Max;
    Vec3 Min;
    
   // Vec3 Collider_position;
public:
    ColliderCube(float _x, float _y, float _z, float _size, GameObject* bind_cube);
    ColliderCube(float _size, GameObject* bind_cube, int type);

    bool AABB_AABB(GameObject* other);
    bool AABB_Sphere(GameObject* _sphere);
    void PrintData();
    virtual void Draw();
    virtual void Update(float deltaTime);
};

