#pragma once
#include "Header.h"
#include "Character.h"

class Spearman : public Character
{
private:
public:
	Spearman();
	Spearman(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage);

	Rectangle getHitbox(Vector2 cameraPos);
	void drawHitbox(Vector2 cameraPos);

	Rectangle getAttackbox(Vector2 cameraPos);
	void drawAttackbox(Vector2 cameraPos);
	bool attackBoxesAreActive();

	void goToPos(Vector2 pos);
	void findTarget(vector<Character> enemies);
	void followTarget(Vector2 pos);
	bool canHitTarget(Rectangle enemyHitbox);

	void holdPosition(Vector2 holdPosition);
	void engage();
	void completelyStop();


};