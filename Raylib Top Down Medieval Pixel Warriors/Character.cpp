#include "Character.h"

Character::Character() {}
Character::Character(AnimationPro idle, AnimationPro run, AnimationPro attack, AnimationPro death, bool facingLeft, Vector2 pos, float speed, float health, float damage)
	: current(idle), idle(idle), run(run), attack(attack), death(death), facingLeft(facingLeft), pos(pos), speed(speed), health(health), damage(damage)
{
	this->pos.x = SCREEN_WIDTH / 2 - current.getWidth() / 2;
	this->pos.y = SCREEN_HEIGHT / 2 - current.getHeight() / 2;

	lastStatus = IDLE;
	status = IDLE;

	isHurt = false;
	isDead = false;

	holdPosition = { 0,0 };
}

float Character::getWidth() { return current.getWidth(); }
float Character::getHeight() { return current.getHeight(); }
Status Character::getStatus() { return status; }
Vector2 Character::getPos() { return pos; }
void Character::setPos(Vector2 pos) { this->pos = pos; }
float Character::getDamage() { return damage; }
bool Character::getIsDead() { return isDead; }

Vector2 Character::getHoldPosition() { return holdPosition; }
void Character::setHoldPosition(Vector2 holdPosition) { this->holdPosition = holdPosition; }

Vector2 Character::getSyncCameraPos() { return { pos.x - (SCREEN_WIDTH / 2 - current.getWidth() / 2), pos.y - (SCREEN_HEIGHT / 2 - current.getHeight() / 2) }; }

void Character::draw(Vector2 cameraPos, Color color)
{
	if (isHurt) current.draw({ pos.x - cameraPos.x, pos.y - cameraPos.y }, facingLeft, RED);
	else current.draw({ pos.x - cameraPos.x, pos.y - cameraPos.y }, facingLeft, color);
	if (!isDead) current.updateFrame();
	endPlayOnceAnimations();
}
void Character::endPlayOnceAnimations()
{
	if (current.atLastFrame())
	{
		if (status == ATTACK) status = IDLE;
		if (status == DEATH) isDead = true;
	}
}

void Character::takeInput()
{
	if (status != DEATH)
	{
		if (IsKeyDown(KEY_F))
		{
			status = ATTACK;
		}
		if (status != ATTACK)
		{
			Vector2 direction{ 0,0 };
			if (IsKeyDown(KEY_W)) direction.y -= 1;
			if (IsKeyDown(KEY_S)) direction.y += 1;
			if (IsKeyDown(KEY_A)) direction.x -= 1;
			if (IsKeyDown(KEY_D)) direction.x += 1;
			if (direction.x < 0) facingLeft = true;
			else if (direction.x > 0) facingLeft = false;
			if (Vector2Length(direction) != 0)
			{
				direction = Vector2Normalize(direction);
				direction = Vector2Scale(direction, speed * GetFrameTime());
				pos = Vector2Add(pos, direction);
				status = RUN;
			}
			else status = IDLE;
		}

		if (IsKeyDown(KEY_Y))
		{
			isHurt = true; //Delete Later
			health -= 10;
		}
		else isHurt = false; //Delete Later
	}
}

void Character::checkDeath()
{
	if (health <= 0) status = DEATH;
}

void Character::changeAnimation()
{
	if (lastStatus != status && lastStatus != DEATH)
	{
		if (status == IDLE) current = idle;
		if (status == RUN) current = run;
		if (status == ATTACK) current = attack;
		if (status == DEATH) current = death;
	}
	lastStatus = status;
}

void Character::checkBound(Vector2 mapSize)
{
	if (pos.x < 0) pos.x = 0;
	else if (pos.x > mapSize.x - current.getWidth()) pos.x = mapSize.x - current.getWidth();
	if (pos.y < 0) pos.y = 0;
	else if (pos.y > mapSize.y - current.getHeight()) pos.y = mapSize.y - current.getHeight();
}

void Character::unloadTexture()
{
	attack.unloadTexture();
	death.unloadTexture();
	idle.unloadTexture();
	run.unloadTexture();
}