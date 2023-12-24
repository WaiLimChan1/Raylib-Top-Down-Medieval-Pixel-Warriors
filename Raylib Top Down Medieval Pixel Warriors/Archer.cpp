#include "Archer.h"

Archer::Archer() {}
Archer::Archer(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage, Arrow arrow)
	: Character(idle, run, attack, death, facingLeft, pos, speed, health, damage), arrow(arrow)
{
	readyToShoot = true;
}

Rectangle Archer::getHitbox(Vector2 cameraPos)
{
	float width = current.getWidth() / 3;
	float height = current.getHeight() / 2;
	float x = pos.x - cameraPos.x + width;
	float y = pos.y - cameraPos.y + height;
	return Rectangle{ x, y, width, height };
}
void Archer::drawHitbox(Vector2 cameraPos) { DrawRectangleRec(getHitbox(cameraPos), { 0, 228, 48, 150 }); }

Arrow Archer::fireArrow()
{
	Arrow result = arrow;
	result.setPos(pos);
	result.setFacingLeft(facingLeft);
	return result;
}
bool Archer::attackBoxesAreActive() { return status == ATTACK && current.getFrame() == 7 && current.getRunningTime() == 0.0f; } //Frame Number 7 (Starting From 1)

void Archer::goToPos(Vector2 pos)
{
	Vector2 changePosition = Vector2Subtract(pos, this->pos);
	if (Vector2Length(changePosition) > 5)
	{
		changePosition = Vector2Normalize(changePosition);
		changePosition = Vector2Scale(changePosition, speed * GetFrameTime());
		if (changePosition.x < 0) facingLeft = true;
		else if (changePosition.x > 0) facingLeft = false;
		this->pos = Vector2Add(this->pos, changePosition);
	}
}
//void Archer::findTarget(vector<Character> enemies);
//void Archer::followTarget(Vector2 pos);
//bool Archer::canHitTarget(Rectangle enemyHitbox);


void Archer::holdPosition(Vector2 holdPosition)
{
	goToPos(holdPosition);
}

void Archer::engage()
{

}

void Archer::completelyStop()
{
	status = IDLE;
}
