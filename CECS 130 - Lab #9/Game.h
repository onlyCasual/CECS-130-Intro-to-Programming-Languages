/*
	Name: Robert Wickliffe
	Description: Create a game of Tic-Tac-Toe.
	Section: CECS 130-01A
	Date: April 1, 2022
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>

// Possible teams to play as
enum Team
{
	NONE,
	X,
	O
};

// Mapping tile characters to team values
const char symbols[3] = { ' ', 'x', 'o' };
const Team teams[3] = { NONE, X, O };

// Generate a psudo-random number ( 0 <= num < max )
int Random(int max);

// Tile on the game board
class Tile
{
public:
	// Tiles assigned team / Team that moved on tile
	Team team;

	// Adjacent tiles on game board
	Tile* tl;
	Tile* t;
	Tile* tr;
	Tile* r;
	Tile* br;
	Tile* b;
	Tile* bl;
	Tile* l;
};

class Game
{
	// Size of game board
	int size;

	// Number of occupied tiles
	int occupied;

	// Where team moves will be stored
	Tile** board;

	// Team the player is assigned to
	Team team;

	// Team that has the current move
	Team turn;

public:
	Game(int size);
	~Game();

	// Start the game
	void Begin();

	// Have team with current turn make a move
	void DoTurn();

	// Choose and make move, when AI team has turn
	void ChooseBestMove();

	// Display the game board
	void Display();

	// Get the team at a given tile, if available
	Team At(short row, short col);

	// Get the team character at a given tile, if available
	char AsChar(short row, short col);

	// Check if the given tile is valid
	bool IsValid(short row, short col);

	// Check if no team has assigned a move to the given tile
	bool IsAvailable(short row, short col);

	// Check if as team reaches the win requirements
	bool HasWinner();
	
	// Set a tile to the supplied team, if available
	bool SetBoardSpace(short row, short col, Team team);

	// Reset the game board
	void Reset();
};
