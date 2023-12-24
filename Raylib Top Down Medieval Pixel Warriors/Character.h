#pragma once
#include "Header.h"
#include "ConstGlobalVariables.cpp"
#include "AnimationPro.h"

class Character
{
protected:
	AnimationPro current;

	AnimationPro idle;
	AnimationPro run;
	AnimationPro attack;
	AnimationPro death;

	Status lastStatus;
	Status status;

	bool facingLeft;

	Vector2 pos;
	float speed;

	float health;
	float damage;
	bool isHurt; // Being attack at this frame
	bool isDead; // Health <= 0 and death animation is complete

	Vector2 holdPosition;

public:
	Character();
	Character(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage);

	float getWidth();
	float getHeight();
	Status getStatus();
	Vector2 getPos();
	void setPos(Vector2 pos);
	float getDamage();
	bool getIsDead();

	Vector2 getHoldPosition();
	void setHoldPosition(Vector2 holdPosition);

	Vector2 getSyncCameraPos();

	void draw(Vector2 cameraPos, Color color = WHITE);
	void endPlayOnceAnimations();
	void takeInput();

	void checkDeath();

	void changeAnimation();
	void checkBound(Vector2 mapSize);

	void unloadTexture();
};
