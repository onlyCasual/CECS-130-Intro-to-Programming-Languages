/*
	Name: Robert Wickliffe
	Description: Create a game of Tic-Tac-Toe
	Section: CECS 130-01A
	Date: February 28, 2022
*/

#include "Game3D.h"

int main()
{
	// Seed rand
	srand(time(NULL));

	// Create a new Game instance
	Game3D game = Game3D(3, 3);
	char play = ' ';

	// Begin the game
	game.Begin();

	// If the player wants to play again
	while (play != 'n')
	{
		// Request user to enter a char
		std::cout << "Would you like to play again? ( y/n ): ";
		std::cin >> play;

		// If entered char is not a valid option
		while (play != 'y' && play != 'n')
		{
			std::cout << "Please enter a valid option ( y/n ): ";
			std::cin >> play;
		};

		// If user want to play again restart game
		if (play == 'y')
			game.Begin();
		else
			break;
	};

	return 0;
};