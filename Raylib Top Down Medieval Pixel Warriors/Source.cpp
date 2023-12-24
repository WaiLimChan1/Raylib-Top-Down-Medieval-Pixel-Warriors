#include "Header.h"
#include "ConstGlobalVariables.cpp"

#include "Background.h"
#include "myCamera.h"

#include "AnimationPro.h"
#include "Character.h"

#include "Spearman.h"
#include "SpearmenUnit.h"

#include "Arrow.h"
#include "Archer.h"
#include "ArcherUnit.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Instructions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// UP, DOWN, LEFT, RIGHT ARROW KEYS : MOVE CAMERA
// T : SYNC CAMERA
// 
// W, S, A, D : MOVE UNIT
// F : UNIT ATTACK
// 
// U : SELECT SPEARMEN
// I : SELECT ARCHERS
// O : SELECT KNIGHT
// 
// LEFT MOUSE BUTTON : HOLD THIS POSITION
// RIGHT MOUSE BUTTON : ENGAGE ENEMY
// SPACE : STOP COMPLETELY
// 
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Global Variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
myCamera camera;
Background background;



//Player--------------------------
ChosenGroup chosenGroup;

int numOfSpearmen;
SpearmenUnit spearmenUnit;

int numOfArcher;
ArcherUnit archerUnit;
//--------------------------------



//Enemy---------------------------
ChosenGroup enemyChosenGroup;

int numOfEnemySpearmen;
SpearmenUnit enemySpearmenUnit;

int numOfEnemyArcher;
ArcherUnit enemyArcherUnit;
//--------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void SetUp()
{
	float scale = 4.0f;
	bool facingLeft = false;
	Vector2 pos{ 0,0 };

	camera = myCamera({ 0,0 }, 600.0f, false);
	background = Background(LoadTexture("textures/WorldMap.png"), { 0,0 }, scale);

	chosenGroup = SPEARMEN;
	enemyChosenGroup = SPEARMEN;

	// Spearman
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	float spearmanUpdateTime = 1.0 / 12.0;
	float spearmanSpeed = 300.0f;
	float spearmanHealth = 100;
	float spearmanDamage = 20;

	AnimationPro spearmanIdle(LoadTexture("textures/Spearman/idle.png"), scale, spearmanUpdateTime * 3 / 2, 1, 5, 5);
	AnimationPro spearmanRun(LoadTexture("textures/Spearman/run.png"), scale, spearmanUpdateTime, 1, 10, 10);
	AnimationPro spearmanAttack(LoadTexture("textures/Spearman/attack.png"), scale, spearmanUpdateTime * 3 / 4, 1, 10, 10);
	AnimationPro spearmanDeath(LoadTexture("textures/Spearman/death.png"), scale, spearmanUpdateTime, 1, 7, 7);
	Spearman spearman = Spearman(spearmanIdle, spearmanRun, spearmanAttack, spearmanDeath, facingLeft, pos, spearmanSpeed, spearmanHealth, spearmanDamage);
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Arrow
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	float arrowRangeDistance = 2000;
	float arrowSpeed = 800;
	float arrowDamage = 50;
	Arrow arrow = Arrow(LoadTexture("textures/Archer/arrow.png"), scale, {0,0}, facingLeft, arrowRangeDistance, arrowSpeed, arrowDamage);
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Archer
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	float archerUpdateTime = 1.0 / 12.0;
	float archerSpeed = 350.0f;
	float archerHealth = 50;
	float archerDamage = arrowDamage;

	AnimationPro archerIdle(LoadTexture("textures/Archer/idle.png"), scale, archerUpdateTime * 3 / 2, 1, 5, 5);
	AnimationPro archerRun(LoadTexture("textures/Archer/run.png"), scale, archerUpdateTime, 1, 10, 10);
	AnimationPro archerAttack(LoadTexture("textures/Archer/attack.png"), scale, archerUpdateTime * 3 / 4, 1, 9, 9);
	AnimationPro archerDeath(LoadTexture("textures/Archer/death.png"), scale, archerUpdateTime, 1, 7, 7);
	Archer archer = Archer(archerIdle, archerRun, archerAttack, archerDeath, facingLeft, pos, archerSpeed, archerHealth, archerDamage, arrow);
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Player
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Generating Spearmen
	numOfSpearmen = 100;
	for (int i = 0; i < numOfSpearmen; i++)
	{
		Vector2 randPos{ rand() % (int)background.getScaledSize().x, rand() % (int)background.getScaledSize().y };
		//Vector2 randPos{ rand() % 250 + 500, rand() % (int)background.getScaledSize().y / 5 };
		spearman.setPos(randPos);
		spearmenUnit.push_back(spearman);
	}

	// Generating Archer
	numOfArcher = 100;
	for (int i = 0; i < numOfArcher; i++)
	{
		Vector2 randPos{ rand() % (int)background.getScaledSize().x, rand() % (int)background.getScaledSize().y };
		//Vector2 randPos{ rand() % 200 + 200, rand() % (int)background.getScaledSize().y / 5 };
		archer.setPos(randPos);
		archerUnit.push_back(archer);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Enemy
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Generating Spearmen
	/*
	numOfEnemySpearmen = 100;
	for (int i = 0; i < numOfEnemySpearmen; i++)
	{
		Vector2 randPos{ rand() % (int)background.getScaledSize().x, rand() % (int)background.getScaledSize().y };
		//Vector2 randPos{ rand() % 250 + 500, rand() % (int)background.getScaledSize().y / 5 };
		spearman.setPos(randPos);
		enemySpearmenUnit.push_back(spearman);
	}

	// Generating Archer
	numOfEnemyArcher = 100;
	for (int i = 0; i < numOfEnemyArcher; i++)
	{
		Vector2 randPos{ rand() % (int)background.getScaledSize().x, rand() % (int)background.getScaledSize().y };
		//Vector2 randPos{ rand() % 200 + 200, rand() % (int)background.getScaledSize().y / 5 };
		archer.setPos(randPos);
		enemyArcherUnit.push_back(archer);
	}
	*/
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	background.draw(camera.getPos());

	spearmenUnit.runDraw(chosenGroup, camera.getPos());
	archerUnit.runDraw(chosenGroup, camera.getPos());

	enemySpearmenUnit.runDraw(chosenGroup, camera.getPos(), PURPLE);
	enemyArcherUnit.runDraw(chosenGroup, camera.getPos(), PURPLE);

	EndDrawing();
}

void Input()
{
	if (IsKeyPressed(KEY_U)) chosenGroup = SPEARMEN;
	if (IsKeyPressed(KEY_I)) chosenGroup = ARCHERS;
	if (IsKeyPressed(KEY_O)) chosenGroup = KNIGHTS;

	if (chosenGroup == SPEARMEN) spearmenUnit.runTakeInput();
	if (chosenGroup == ARCHERS) archerUnit.runTakeInput();
	if (chosenGroup == KNIGHTS) {}

	//if (enemyChosenGroup == SPEARMEN) enemySpearmenUnit.runTakeInput();
	//if (enemyChosenGroup == ARCHERS) enemyArcherUnit.runTakeInput();
	//if (enemyChosenGroup == KNIGHTS) {}

	camera.takeInput();
}

void Logic()
{
	if (chosenGroup == SPEARMEN) spearmenUnit.runCommandCalculationsIfNecessary(camera.getPos());
	spearmenUnit.runLogic(background.getScaledSize());
	if (chosenGroup == ARCHERS) archerUnit.runCommandCalculationsIfNecessary(camera.getPos());
	archerUnit.runLogic(background.getScaledSize());

	//if (enemyChosenGroup == SPEARMEN) enemySpearmenUnit.runCommandCalculationsIfNecessary(camera.getPos());
	//enemySpearmenUnit.runLogic(background.getScaledSize());
	//if (enemyChosenGroup == ARCHERS) enemyArcherUnit.runCommandCalculationsIfNecessary(camera.getPos());
	//enemyArcherUnit.runLogic(background.getScaledSize());

	//if (camera.getLocked()) camera.setPos(spearman.getSyncCameraPos());
	camera.checkBound(background.getScaledSize());
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Top Down Medieval Pixel Warriors");
	SetWindowState(FLAG_VSYNC_HINT);
	srand(time(0));

	SetUp();
	while (!WindowShouldClose())
	{
		Draw();
		Input();
		Logic();
	}
	background.unloadTexture();
	//unload spearmen, archer, arrow
	CloseWindow();
	return 0;
}