/*
	Name: Robert Wickliffe
	Description: Create a 3D game of Tic-Tac-Toe.
	Section: CECS 130-01A
	Date: April 15, 2022
*/

#include "Game3D.h"

void Game3D::Display()
{
	std::cout << "--------------------------------" << std::endl;

	// Print each board in game
	for (int i = 0; i < this->games; ++i)
	{
		char board = 'a' + i;

		std::cout << "[ Board " << (char)toupper(board) << " ]" << std::endl;
		this->boards[i]->Display();
	};

	std::cout << "--------------------------------" << std::endl;
};

void Game3D::Begin()
{
	// Reset the board
	this->Reset();

	// User's team
	char team = ' ';
	Team turn = NONE;

	// Request the user to choose a team
	std::cout << "Please choose a team ( x, o ): ";
	std::cin >> team;

	while (tolower(team) != 'x' && tolower(team) != 'o')
	{
		std::cout << "Please enter a valid team ( x, o ): ";
		std::cin >> team;
	};

	// Print team and set team variable
	std::cout << "You have been assigned to Team " << (char)toupper(team) << "." << std::endl;
	this->SetTeams(team == 'x' ? X : O);

	// Choose a random team to start first
	while (turn == NONE)
		turn = teams[Random(3)];

	this->SetTurns(turn);

	// Display the board and print who has first move
	this->Display();

	std::cout << "Team " << (this->turn == X ? 'X' : 'O') << " has the first move." << std::endl;

	// Make current team take their turn
	this->DoTurn();
};

void Game3D::DoTurn()
{
	// Wins for each team and draws
	int pwins = 0;
	int aiwins = 0;
	int draws = 0;

	// Loop through boards and check for wins
	for (int i = 0; i < this->games; ++i)
	{
		// Team of the winner on board
		Team winner = this->boards[i]->HasWinner();

		// Increment respective variables base off winning team
		if (winner == this->team)
			pwins++;
		else if (winner && winner != this->team)
			aiwins++;
		else
			if (!winner && this->boards[i]->Occupied() == pow(this->size, 2))
				draws++;
	};

	// If all boards have a winner
	if ((pwins + aiwins + draws) == this->games)
	{
		if (aiwins > pwins)
			std::cout << "The game is over, Team " << (this->team == X ? "O" : "X") << " wins. " << "They had " << aiwins << " wins." << std::endl;
		else if(pwins > aiwins)
			std::cout << "The game is over, Team " << (this->team == X ? "X" : "O") << " wins. " << "They had " << pwins << " wins." << std::endl;
		else
			std::cout << "The game is over, It was a draw. Both teams had " << pwins << " wins." << std::endl;

		return;
	};

	// If it is currently the user's turn else have the AI team make a move
	if (this->turn == this->team)
	{
		// Board the player is making a move on
		char board;

		// Request the user to choose a board
		std::cout << "Please choose a board ( Ex. B ): ";
		std::cin >> board;

		while (tolower(board) < 'a' || tolower(board) > ('a' + this->games))
		{
			std::cout << "Please choose a valid board ( Ex. B ): ";
			std::cin >> board;
		};

		// The index of the users chosen board
		int index = tolower(board) - 'a';

		// If the chosen board has a winner
		Team winner = this->boards[index]->HasWinner();

		// EEnsure the chosen board does not have a winner
		if (winner)
		{
			std::cout << "There is already a winner for this board, Please try again." << std::endl;
			return this->DoTurn();
		}
		else
		{
			if (this->boards[index]->Occupied() == pow(this->size, 2))
			{
				std::cout << "All the tiles in this board have already been filled, Please try again." << std::endl;
				return this->DoTurn();
			};
		};

		// Have the user make a move on the chosen board
		this->boards[index]->DoTurn();

		// Set the last move to the board index of the users last board move
		if(this->last_move == index)
			this->moves++;
		else
			this->moves = 1;
		
		this->last_move = index;
		
		// Check if the board now has a winner
		winner = this->boards[index]->HasWinner();

		if (winner)
			std::cout << "Team " << (this->turn == X ? "X" : "O") << " has gotten 3 in a row on Board " << (char)(board) << "." << std::endl;
		else
			if (this->boards[index]->Occupied() == pow(this->size, 2))
				std::cout << "There has been a draw on Board " << (char)toupper(board) << "." << std::endl;
	}
	else
	{
		// Index of the board for the AI to make a move on
		int index = 0;
		
		if(this->moves > 1)
			index = this->last_move;
		else
			index = Random(this->games);

		// Check if the board has a winner
		Team winner = this->boards[index]->HasWinner();

		// If the board has a winner, find a board that doesnt have a winner
		while (winner || !winner && this->boards[index]->Occupied() == pow(this->size, 2))
		{
			index = Random(this->games);
			winner = this->boards[index]->HasWinner();
		};

		// Have the AI make a move on the chosen board
		this->boards[index]->DoTurn();
		
		winner = this->boards[index]->HasWinner();

		// Check of the board now has a winner
		if (winner)
			std::cout << "Team " << (this->turn == X ? "X" : "O") << " has gotten 3 in a row on Board " << (char)toupper('a' + index) << "." << std::endl;
		else
			if (this->boards[index]->Occupied() == pow(this->size, 2))
				std::cout << "There has been a draw on Board " << (char)toupper('a' + index) << "." << std::endl;
	};

	// Switch thee current turn to the opposing team
	if (this->turn == O)
		this->SetTurns(X);
	else
		this->SetTurns(O);

	// Display the game boards
	this->Display();

	// Have next turn make a move on game board
	this->DoTurn();
};

void Game3D::Reset()
{
	// Loop through game boards and reset them
	for (int i = 0; i < this->games; ++i)
		this->boards[i]->Reset();
};

void Game3D::SetTurns(Team team)
{
	// Set turn of game to given team
	this->turn = team;

	// Loop through game boards and set turn to given team
	for (int i = 0; i < this->games; ++i)
		this->boards[i]->SetTurn(team);
};

void Game3D::SetTeams(Team team)
{
	// Set player team of game board to given team
	this->team = team;

	// Loop through game boards and set player team to given team
	for (int i = 0; i < this->games; ++i)
		this->boards[i]->SetPlayerTeam(team);
};
