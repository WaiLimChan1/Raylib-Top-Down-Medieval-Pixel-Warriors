#include "Arrow.h"

Arrow::Arrow() {}
Arrow::Arrow(Texture2D texture, float scale, Vector2 pos, bool facingLeft, float rangeDistance, float speed, float damage)
	: texture(texture), scale(scale), pos(pos), facingLeft(facingLeft), rangeDistance(rangeDistance), speed(speed), damage(damage)
{
	traveledDistance = 0;
	isDone = false;
}

Vector2 Arrow::getPos() { return pos; }
void Arrow::setPos(Vector2 pos) { this->pos = pos; }
void Arrow::setFacingLeft(bool facingLeft) { this->facingLeft = facingLeft; }
float Arrow::getDamage() { return damage * getRemainingDistanceRatio() / 2; } // 50 Percent Damage Fall Off
bool Arrow::getIsDone() { return isDone; }
void Arrow::setIsDone(bool isDone) { this->isDone = isDone; }
float Arrow::getRemainingDistanceRatio() { return (rangeDistance - traveledDistance) / (rangeDistance); }

Rectangle Arrow::getAttackbox(Vector2 cameraPos)
{
	float width = scale * texture.width / 2;
	float height = scale * texture.height / 4;
	float x = pos.x - cameraPos.x + width / 2;
	float y = pos.y - cameraPos.y + height * 5 / 2;
	return Rectangle{ x, y, width, height };
}
void Arrow::drawAttackbox(Vector2 cameraPos) { DrawRectangleRec(getAttackbox(cameraPos), { 255, 161, 0, (unsigned char)(255 * getRemainingDistanceRatio()) }); }
void Arrow::draw(Vector2 cameraPos)
{
	DrawTextureEx(texture, { pos.x - cameraPos.x, pos.y - cameraPos.y }, 0, scale, WHITE);
}
void Arrow::updatePosition()
{
	float distance = speed * GetFrameTime();
	if (facingLeft) pos.x -= distance;
	else pos.x += distance;
	traveledDistance += distance;
}
void Arrow::checkIsDone(Vector2 mapSize)
{
	if (traveledDistance >= rangeDistance) isDone = true;
	if (pos.x < -scale * texture.width || pos.x > mapSize.x || pos.y < -scale * texture.height || pos.y > mapSize.x) isDone = true;
}

void Arrow::unloadTexture() { UnloadTexture(texture); }