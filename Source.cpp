#include "Header.h"

#define INTERVAL 1.0/60.0

using namespace std;

int main() {
	showConsoleCursor(false);
	srand(time(0));
	Display* display = new Display();
	GameEngine* gameEngine = new GameEngine();
	float prev = (float)clock() / CLOCKS_PER_SEC;
	while (true) {
		float curr = (float)clock() / CLOCKS_PER_SEC;
		float dt = curr - prev;

		if (dt < INTERVAL) continue;
		prev = curr;
//		printf("%.3f\n", curr);

		bool left = keyState('a');
		bool right = keyState('d');
		bool down = keyState('s');
		bool rotateccw = keyState('w');
		if (left) {
			gameEngine->next(dt, 'a');
		}
		else if (right) {
			gameEngine->next(dt, 'd');
		}
		else if (down) {
			gameEngine->next(dt, 's');
		}
		else if (rotateccw) {
//			gameEngine->rotate();
		}
		
		gameEngine->next(dt, 0);
		gameEngine->makeDisplayData();
		display->draw();

		if (gameEngine->state == GameEngine::GameState::GAMEOVER) break;

	}

	printf("\033[2J");
	printf("\rgame over!\n");

	return 0;
}
