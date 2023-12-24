#include "Background.h"

Background::Background() {}
Background::Background(Texture2D texture, Vector2 pos, float scale)
	: texture(texture), pos(pos), scale(scale) {}
Vector2 Background::getScaledSize() { return { scale * texture.width, scale * texture.height }; }
void Background::draw(Vector2 cameraPos) { DrawTextureEx(texture, { pos.x - cameraPos.x, pos.y - cameraPos.y }, 0, scale, WHITE); }
void Background::unloadTexture() { UnloadTexture(texture); }