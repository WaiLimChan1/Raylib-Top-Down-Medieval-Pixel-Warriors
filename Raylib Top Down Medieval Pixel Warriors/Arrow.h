#pragma once
#include "Header.h"
#include "ConstGlobalVariables.cpp"

class Arrow
{
	/* STILL NEED TO DO HIT ISDONE*/
private:
	Texture2D texture;
	float scale;

	Vector2 pos;

	bool facingLeft;
	float rangeDistance;
	float traveledDistance;
	float speed;

	float damage;

	bool isDone; //Either hit, reached range, or went out of bound
public:
	Arrow();
	Arrow(Texture2D texture, float scale, Vector2 pos, bool facingLeft, float rangeDistance, float speed, float damage);


	Vector2 getPos();
	void setPos(Vector2 pos);
	void setFacingLeft(bool facingLeft);
	float getDamage();
	bool getIsDone();
	void setIsDone(bool isDone);
	float getRemainingDistanceRatio();

	Rectangle getAttackbox(Vector2 cameraPos);
	void drawAttackbox(Vector2 cameraPos);

	void draw(Vector2 cameraPos);
	void updatePosition();
	void checkIsDone(Vector2 mapSize);

	void unloadTexture();
};
