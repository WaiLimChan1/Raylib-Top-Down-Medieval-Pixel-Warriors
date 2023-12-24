#pragma once
#include "Header.h"
#include "ConstGlobalVariables.cpp"
#include "Spearman.h"

class SpearmenUnit
{
private:
	vector<Spearman> spearmen;

	Command lastCommand;
	Command command;
	Vector2 holdPosition;
public:
	SpearmenUnit();
	SpearmenUnit(vector<Spearman>& spearmen);

	void push_back(Spearman spearman);
	int size();

	Command getCommand();
	bool commandChanged();
	Vector2 getHoldPosition();
	void setHoldPosition(Vector2 holdPosition);

	void printInfo();
	void takeInput();

	void runCommands();

	void runCommandCalculationsIfNecessary(Vector2 cameraPos);
	void commandCalculateHoldPosition(Vector2 cameraPos, int rows);
	void commandCalculateEngage();

	//For Each Spearman
	void runDraw(ChosenGroup chosenGroup, Vector2 cameraPos, Color color = WHITE);
	void runTakeInput();
	void runLogic(Vector2 mapSize);
};