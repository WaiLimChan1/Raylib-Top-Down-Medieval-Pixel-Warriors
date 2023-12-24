#include "myCamera.h"

myCamera::myCamera() {}
myCamera::myCamera(Vector2 pos, float speed, bool locked)
	:pos(pos), speed(speed), locked(locked) {}
Vector2 myCamera::getPos() { return pos; }
void myCamera::setPos(Vector2 pos) { this->pos = pos; }
bool myCamera::getLocked() { return locked; }

void myCamera::takeInput()
{
	float dt = GetFrameTime();
	if (IsKeyDown(KEY_UP)) pos.y -= speed * dt;
	if (IsKeyDown(KEY_DOWN)) pos.y += speed * dt;
	if (IsKeyDown(KEY_LEFT)) pos.x -= speed * dt;
	if (IsKeyDown(KEY_RIGHT)) pos.x += speed * dt;

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) locked = false;
	if (IsKeyDown(KEY_T)) locked = !locked;

}
void myCamera::checkBound(Vector2 mapSize)
{
	if (pos.x < 0) pos.x = 0;
	else if (pos.x > mapSize.x - SCREEN_WIDTH) pos.x = mapSize.x - SCREEN_WIDTH;

	if (pos.y < 0) pos.y = 0;
	else if (pos.y > mapSize.y - SCREEN_HEIGHT) pos.y = mapSize.x - SCREEN_HEIGHT;
}
