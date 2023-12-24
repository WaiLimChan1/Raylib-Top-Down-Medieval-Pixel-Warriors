#pragma once
#include "Header.h"
#include "ConstGlobalVariables.cpp"

class myCamera
{
private:
	Vector2 pos;
	float speed;
	bool locked;

public:
	myCamera();
	myCamera(Vector2 pos, float speed, bool locked);
	Vector2 getPos();
	void setPos(Vector2 pos);
	bool getLocked();
	void takeInput();
	void checkBound(Vector2 mapSize);
};