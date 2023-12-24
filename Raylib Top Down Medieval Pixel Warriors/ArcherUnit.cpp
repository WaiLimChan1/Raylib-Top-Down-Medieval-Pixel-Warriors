#include "ArcherUnit.h"

ArcherUnit::ArcherUnit() {}
ArcherUnit::ArcherUnit(vector<Archer>& archers, vector<Arrow> arrows)
	: archers(archers), arrows(arrows)
{
	lastCommand = PLAYER_INPUT;
	command = PLAYER_INPUT;
	holdPosition = { 0,0 };
}

void ArcherUnit::push_back(Archer archer) { archers.push_back(archer); }
int ArcherUnit::size() { return archers.size(); }

Command ArcherUnit::getCommand() { return command; }
bool ArcherUnit::commandChanged() { return lastCommand != command; }
Vector2 ArcherUnit::getHoldPosition() { return holdPosition; }
void ArcherUnit::setHoldPosition(Vector2 holdPosition) { this->holdPosition = holdPosition; }

void ArcherUnit::printInfo()
{
	char message[50];
	strcpy_s(message, "Archers Command: ");
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

void ArcherUnit::takeInput()
{
	if (IsMouseButtonPressed(0)) command = HOLD_POSITION;
	if (IsMouseButtonPressed(1)) command = ENGAGE;
	if (IsKeyPressed(KEY_SPACE)) command = COMPLETELY_STOP;
	if (IsKeyPressed(KEY_F) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) command = PLAYER_INPUT;
}

void ArcherUnit::runCommands()
{
	if (command != PLAYER_INPUT)
	{
		if (command == HOLD_POSITION) for (auto& archer : archers) archer.holdPosition(archer.getHoldPosition());
		if (command == ENGAGE) for (auto& archer : archers) archer.engage();
		if (command == COMPLETELY_STOP)  for (auto& archer : archers) archer.completelyStop();
	}
	lastCommand = command;
}

void ArcherUnit::runCommandCalculationsIfNecessary(Vector2 cameraPos)
{
	if (archers.size() > 0)
	{
		if (commandChanged() || IsMouseButtonDown(0) || IsMouseButtonDown(1))
		{
			if (command == HOLD_POSITION) commandCalculateHoldPosition(cameraPos, 15);
			if (command == getCommand() == ENGAGE) commandCalculateEngage();
		}
	}
}
void ArcherUnit::commandCalculateHoldPosition(Vector2 cameraPos, int rows)
{
	holdPosition = GetMousePosition();
	holdPosition = { holdPosition.x + cameraPos.x, holdPosition.y + cameraPos.y - archers.at(0).getHeight() * 3 };

	float xOffset = archers.at(0).getWidth() / 6;
	float yOffset = archers.at(0).getHeight() / 3;

	int rowCounter = 0;
	int colCounter = 0;
	for (auto& archer : archers)
	{
		archer.setHoldPosition({ holdPosition.x - xOffset * colCounter, holdPosition.y + yOffset * rowCounter });
		rowCounter++;
		if (rowCounter == rows)
		{
			rowCounter = 0;
			colCounter++;
		}
	}
}
void ArcherUnit::commandCalculateEngage()
{

}

//For Each Archer
void ArcherUnit::runDraw(ChosenGroup chosenGroup, Vector2 cameraPos, Color color)
{
	for (auto& archer : archers)
	{
		//if (chosenGroup == ARCHERS) archer.drawHitbox(camera.getPos());
		archer.draw(cameraPos, color);
	}
	if (chosenGroup == ARCHERS && archers.size() > 0) printInfo();

	for (auto& arrow : arrows)
	{
		//arrow.drawAttackbox(camera.getPos());
		arrow.draw(cameraPos);
	}
}
void ArcherUnit::runTakeInput()
{
	takeInput();
	for (auto& archer : archers) archer.takeInput();
}
void ArcherUnit::runLogic(Vector2 mapSize)
{
	runCommands();
	for (auto& archer : archers)
	{
		if (archer.attackBoxesAreActive()) arrows.push_back(archer.fireArrow());
		archer.checkDeath();
		archer.changeAnimation();
		archer.checkBound(mapSize);
	}

	//Run Arrow Logic And Delete Finished Arrows
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows.at(i).updatePosition();
		arrows.at(i).checkIsDone(mapSize);

		//Delete Finished Arrows
		if (arrows.at(i).getIsDone())
		{
			arrows.erase(next(arrows.begin(), i), next(arrows.begin(), i + 1));
			i--;
		}
	}
}