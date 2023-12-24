#pragma once
#include "Header.h"
#include "ConstGlobalVariables.cpp"
#include "Archer.h"

class ArcherUnit
{
private:
	vector<Archer> archers;
	vector<Arrow> arrows;

	Command lastCommand;
	Command command;
	Vector2 holdPosition;
public:
	ArcherUnit();
	ArcherUnit(vector<Archer>& archers, vector<Arrow> arrows);

	void push_back(Archer archers);
	int size();

	Command getCommand();
	bool commandChanged();
	Vector2 getHoldPosition();
	void setHoldPosition(Vector2 holdPosition);

	void takeInput();
	void printInfo();

	void runCommands();

	void runCommandCalculationsIfNecessary(Vector2 cameraPos);
	void commandCalculateHoldPosition(Vector2 cameraPos, int rows);
	void commandCalculateEngage();

	//For Each Archer
	void runDraw(ChosenGroup chosenGroup, Vector2 cameraPos, Color color = WHITE);
	void runTakeInput();
	void runLogic(Vector2 mapSize);
};