#include "game.hpp"


int main() {
	Snake snake;				// Initialize the Snake object.
	Food food;					// Initialize the Food object.
	Game game(&snake, &food);	// Initialize the Game object, with pointers to snake and food.
	game.run();					// Run the game.
	return 0;
}