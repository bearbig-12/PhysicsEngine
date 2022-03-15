#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	r = 1.0f;
	g = 0.0f;
	b = 1.0f;

	mType = 100;
}

GameObject::GameObject(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;

	r = 1.0f;
	g = 1.0f;
	b = 1.0f;

	mType = 100;

}



GameObject::GameObject(float _x, float _y, float _z, float _r, float _g, float _b)
{
	x = _x;
	y = _y;
	z = _z;

	r = _r;
	g = _g;
	b = _b;

	mType = 100;

}

GameObject::~GameObject()
{
}
