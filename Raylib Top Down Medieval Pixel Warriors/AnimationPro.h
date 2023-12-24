#pragma once
#include "Header.h"

class AnimationPro
{
private:
	Texture2D texture;
	Rectangle source;

	float scale;
	float width;
	float height;

	float updateTime;
	float runningTime;
	int frame;

	int rowFrames;
	int colFrames;
	int totalFrames;

public:
	AnimationPro();
	AnimationPro(Texture2D texture, float scale, float updateTime, int rowFrames, int colFrames, int totalFrames);

	float getWidth();
	float getHeight();
	float getRunningTime();
	int getFrame();

	void draw(Vector2 pos, bool flip);
	void draw(Vector2 pos, bool flip, Color color);
	void updateFrame();

	bool atMidFrame();
	bool atLastFrame();

	void unloadTexture();
};