#pragma once
#include "Game.h"

class Game3D : public Game
{
	// Number of boards / concurrent games
	int games;

	// Index of board the player last made a move on
	int last_move;
	
	// Number of tmoves player has made in last move board
	int moves;

	// Game boards
	Game** boards;

public:
	Game3D(int games, int size) : Game(size)
	{
		this->games = games;
		this->last_move = Random(this->games);
		this->moves = 0;

		// Create array to store game boards
		this->boards = new Game * [games];

		// Create game boards
		for (int i = 0; i < games; ++i)
			this->boards[i] = new Game(size);
	};

	~Game3D()
	{
		// Free game boards
		for (int i = 0; i < this->games; ++i)
			delete this->boards[i];

		// Free board array
		delete this->boards;
	};

	// Begin the game
	void Begin();

	// Display the game boards
	void Display();

	// Have the current turn complete their turn
	void DoTurn();

	// Reset the game boards
	void Reset();

	// The the player team of the game boards
	void SetTeams(Team team);

	// Set the current turn of the game boards
	void SetTurns(Team team);
};
