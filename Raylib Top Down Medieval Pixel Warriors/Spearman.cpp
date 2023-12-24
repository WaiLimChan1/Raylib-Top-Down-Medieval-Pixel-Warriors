#include "Spearman.h"

Spearman::Spearman() {}
Spearman::Spearman(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage)
	: Character(idle, run, attack, death, facingLeft, pos, speed, health, damage) {}

Rectangle Spearman::getHitbox(Vector2 cameraPos)
{
	float width = current.getWidth() / 3;
	float height = current.getHeight() / 2;
	float x = pos.x - cameraPos.x + width;
	float y = pos.y - cameraPos.y + height;
	return Rectangle{ x, y, width, height };
}
void Spearman::drawHitbox(Vector2 cameraPos) { DrawRectangleRec(getHitbox(cameraPos), { 0, 228, 48, 150 }); }

Rectangle Spearman::getAttackbox(Vector2 cameraPos)
{
	if (attackBoxesAreActive())
	{
		float width = current.getWidth() / 3;
		float height = current.getHeight() / 2;
		float x = pos.x - cameraPos.x + width;
		float y = pos.y - cameraPos.y + height;
		if (facingLeft) x -= width;
		else x += width;
		return Rectangle{ x, y, width, height };
	}
	else return Rectangle{ 0, 0, 0, 0 };
}
void Spearman::drawAttackbox(Vector2 cameraPos) { DrawRectangleRec(getAttackbox(cameraPos), { 255, 161, 0, 150 }); }
bool Spearman::attackBoxesAreActive() { return status == ATTACK && current.getFrame() == 7; } //Frame Number 7 (Starting From 1)

void Spearman::goToPos(Vector2 pos)
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
//void Spearman::findTarget(vector<Character> enemies);
//void Spearman::followTarget(Vector2 pos);
//bool Spearman::canHitTarget(Rectangle enemyHitbox);

void Spearman::holdPosition(Vector2 holdPosition)
{
	goToPos(holdPosition);
}
void Spearman::engage()
{

}
void Spearman::completelyStop()
{
	status = IDLE;
}