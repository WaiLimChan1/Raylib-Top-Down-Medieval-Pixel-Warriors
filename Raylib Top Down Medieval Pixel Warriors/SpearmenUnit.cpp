#include "SpearmenUnit.h"

SpearmenUnit::SpearmenUnit() {}
SpearmenUnit::SpearmenUnit(vector<Spearman>& spearmen)
	: spearmen(spearmen)
{
	lastCommand = PLAYER_INPUT;
	command = PLAYER_INPUT;
	holdPosition = { 0,0 };
}

void SpearmenUnit::push_back(Spearman spearman) { spearmen.push_back(spearman); }
int SpearmenUnit::size() { return spearmen.size(); }

Command SpearmenUnit::getCommand() { return command; }
bool SpearmenUnit::commandChanged() { return lastCommand != command; }
Vector2 SpearmenUnit::getHoldPosition() { return holdPosition; }
void SpearmenUnit::setHoldPosition(Vector2 holdPosition) { this->holdPosition = holdPosition; }

void SpearmenUnit::printInfo()
{
	char message[50];
	strcpy_s(message, "Spearmen Command: ");
	if (command == PLAYER_INPUT) strcat_s(message, "Player Input");
	if (command == HOLD_POSITION) strcat_s(message, "Hold Position");
	if (command == ENGAGE) strcat_s(message, "Engage");
	if (command == COMPLETELY_STOP) strcat_s(message, "Completely Stop");
	DrawText(message, 0, 0, 40, WHITE);

	strcpy_s(message, "HoldPosition: (");
	strcat_s(message, to_string((int)holdPosition.x).c_str());
	strcat_s(message, ", ");
	strcat_s(message, to_string((int)holdPosition.y).c_str());
	strcat_s(message, ")");
	DrawText(message, 0, 40, 40, WHITE);
}

void SpearmenUnit::takeInput()
{
	if (IsMouseButtonPressed(0)) command = HOLD_POSITION;
	if (IsMouseButtonPressed(1)) command = ENGAGE;
	if (IsKeyPressed(KEY_SPACE)) command = COMPLETELY_STOP;
	if (IsKeyPressed(KEY_F) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) command = PLAYER_INPUT;
}

void SpearmenUnit::runCommands()
{
	if (command != PLAYER_INPUT)
	{
		if (command == HOLD_POSITION) for (auto& spearman : spearmen) spearman.holdPosition(spearman.getHoldPosition());
		if (command == ENGAGE) for (auto& spearman : spearmen) spearman.engage();
		if (command == COMPLETELY_STOP)  for (auto& spearman : spearmen) spearman.completelyStop();
	}
	lastCommand = command;
}

void SpearmenUnit::runCommandCalculationsIfNecessary(Vector2 cameraPos)
{
	if (spearmen.size() > 0)
	{
		if (commandChanged() || IsMouseButtonDown(0) || IsMouseButtonDown(1))
		{
			if (command == HOLD_POSITION) commandCalculateHoldPosition(cameraPos, 15);
			if (command == getCommand() == ENGAGE) commandCalculateEngage();
		}
	}
}
void SpearmenUnit::commandCalculateHoldPosition(Vector2 cameraPos, int rows)
{
	holdPosition = GetMousePosition();
	holdPosition = { holdPosition.x + cameraPos.x, holdPosition.y + cameraPos.y - spearmen.at(0).getHeight() * 3 };

	float xOffset = spearmen.at(0).getWidth() / 6;
	float yOffset = spearmen.at(0).getHeight() / 3;

	int rowCounter = 0;
	int colCounter = 0;
	for (auto& spearman : spearmen)
	{
		spearman.setHoldPosition({ holdPosition.x - xOffset * colCounter, holdPosition.y + yOffset * rowCounter });
		rowCounter++;
		if (rowCounter == rows)
		{
			rowCounter = 0;
			colCounter++;
		}
	}
}
void SpearmenUnit::commandCalculateEngage()
{

}

void SpearmenUnit::runDraw(ChosenGroup chosenGroup, Vector2 cameraPos, Color color)
{
	for (auto& spearman : spearmen)
	{
		//spearman.drawAttackbox(cameraPos);
		//if (chosenGroup == SPEARMEN) spearman.drawHitbox(cameraPos);
		spearman.draw(cameraPos, color);
	}
	if (chosenGroup == SPEARMEN && spearmen.size() > 0) printInfo();
}
void SpearmenUnit::runTakeInput()
{
	takeInput();
	for (auto& spearman : spearmen) spearman.takeInput();
}
void SpearmenUnit::runLogic(Vector2 mapSize)
{
	runCommands();
	for (auto& spearman : spearmen)
	{
		spearman.checkDeath();
		spearman.changeAnimation();
		spearman.checkBound(mapSize);
	}
}