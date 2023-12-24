#pragma once
#include "Header.h"
#include "Character.h"
#include "Arrow.h"

class Archer : public Character
{
private:
	Arrow arrow;
	bool readyToShoot;
public:
	Archer();
	Archer(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage, Arrow arrow);

	Rectangle getHitbox(Vector2 cameraPos);
	void drawHitbox(Vector2 cameraPos);

	Arrow fireArrow();
	bool attackBoxesAreActive();

	void goToPos(Vector2 pos);
	void findTarget(vector<Character> enemies);
	void followTarget(Vector2 pos);
	bool canHitTarget(Rectangle enemyHitbox);

	void holdPosition(Vector2 holdPosition);
	void engage();
	void completelyStop();
};