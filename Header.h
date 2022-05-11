#define _CRT_SECURE_NO_WARNINGS

#include "TetrisHelper.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>

#define GRID_WIDTH 7
#define GRID_HEIGHT 10
#define USERBLOCK_SIZE 3

int displayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };

class Display {
public:
	void draw() {
		for (int i = 0; i < GRID_HEIGHT; i++) {
			for (int j = 0; j < GRID_WIDTH; j++) {
				drawPosition(j, i, displayData[i][j] == 1);
			}
		}
	}
};

class GameEngine {
public:
	enum class GameState {
		PLAYING, GAMEOVER
	};

	GameState state = GameState::PLAYING;

	int gameGridData[GRID_HEIGHT][GRID_WIDTH] = {
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	int userBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = {
		{1, 0, 0},
		{1, 0, 0},
		{1, 0, 0}
	};
	int blockX = 0, blockY = 0;

	float elapsed = 0.0f;
	float controlCheck = 0.0f;

	void init() {
		makeUserBlock();
	}

	void next(float dt, char keyboardInput) {
		elapsed += dt;
		if (elapsed >= 0.5f) {
			if (canGoDown()) {
				blockY++;
			}
			else {
				trans();
				if(gameOverDecision()) state = GameState::GAMEOVER;
			}
			
			elapsed = elapsed - 0.5f;
		}

		controlCheck = controlCheck + dt;

		if (keyboardInput == 'a' && canGoLeft() && controlCheck > 0.1)
		{
			blockX--;
			controlCheck = 0.0f;
		}
		if (keyboardInput == 'd' && canGoRight() && controlCheck > 0.1)
		{
			blockX++;
			controlCheck = 0.0f;
		}
		if (keyboardInput == 's' && canGoDown() && controlCheck > 0.1)
		{
			blockY++;
			controlCheck = 0.0f;
		}
	}

	void rotate() {

	}

	bool gameOverDecision() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				if (userBlock[i][j] == 1 && gameGridData[i + blockY][j + blockX] == 1) {
					return true;
				}
				else return false;
			}
		}
	}

	bool canGoDown() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				if (userBlock[i][j] == 1 && i + blockY + 1 >= GRID_HEIGHT)
					return false;
				if (userBlock[i][j] == 1 && gameGridData[i + blockY + 1][j + blockX] == 1)
					return false;			
			}
		}
		return true;
	}

	bool canGoLeft() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				if (userBlock[i][j] == 1 && j + blockX - 1 < 0) {
					return false;
				}
				if (userBlock[i][j] == 1 && gameGridData[i + blockY][j + blockX - 1] == 1) {
					return false;
				}
			}
		}
		return true;
	}

	bool canGoRight() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				if (userBlock[i][j] == 1 && j + blockX + 1 > GRID_WIDTH - 1) {
					return false;
				}
				if (userBlock[i][j] == 1 && gameGridData[i + blockY][j + blockX + 1] == 1) {
					return false;
				}
			}
		}
		return true;
	}

	bool isLineFilled(int y) {
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			if (gameGridData[y][i] == 0) return false;
		}
		return true;
	}

	void eraseLine(int y) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			gameGridData[y][i] = 0;
		}
	}

	void drop(int y) {
		for (int i = y; i >= 0; i--) {
			for (int j = 0; j < GRID_WIDTH; j++) {
				gameGridData[i][j] = i - 1 < 0 ? 0 : gameGridData[i - 1][j];
			}
		}
	}

	void trans() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				gameGridData[i + blockY][j + blockX] = userBlock[i][j] | gameGridData[i + blockY][j + blockX];
			}
		}
		for (int i = 0; i < GRID_HEIGHT; i++) {
			if (isLineFilled(i)) {
				eraseLine(i);
				drop(i);
			}
		}

		makeUserBlock();
	}

	int userBlockVarious[7][USERBLOCK_SIZE][USERBLOCK_SIZE] = {
		{
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0}
		},
		{
			{0, 0, 0},
			{1, 1, 0},
			{1, 1, 0}
		},
		{
			{0, 0, 0},
			{0, 1, 0},
			{1, 1, 1}
		},
		{
			{0, 1, 0},
			{0, 1, 0},
			{1, 1, 0}
		},
		{
			{1, 0, 0},
			{1, 0, 0},
			{1, 1, 0}
		},
		{
			{0, 0, 0},
			{1, 1, 0},
			{0, 1, 1}
		},
		{
			{0, 0, 0},
			{0, 1, 1},
			{1, 1, 0}
		}
	};
	
	void makeUserBlock() {
		blockX = GRID_WIDTH / 2 - USERBLOCK_SIZE / 2;
		blockY = 0;

		int various = rand() % 7;
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int j = 0; j < USERBLOCK_SIZE; j++) {
				userBlock[i][j] = userBlockVarious[various][i][j];
			}
		}
	}

	void makeDisplayData() {
		for (int i = 0; i < GRID_HEIGHT; i++) {
			for (int j = 0; j < GRID_WIDTH; j++) {
				displayData[i][j] = gameGridData[i][j];
			}
		}
		for (int i = 0; i < USERBLOCK_SIZE; i++){
			for (int j = 0; j < USERBLOCK_SIZE; j++){
				if (i + blockY < 0 || i + blockY > GRID_HEIGHT) {
					
				}
				else if (j + blockX < 0 || j + blockX > GRID_WIDTH) {

				}
				else {
					displayData[i + blockY][j + blockX] = userBlock[i][j] | displayData[i+blockY][j+blockX];
				}
			}
		}
	}
};