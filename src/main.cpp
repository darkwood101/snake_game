#include "game.hpp"

int main() {
	Snake snake;
	Food food;
	Game game(&snake, &food);
	game.run();
	return 0;
}