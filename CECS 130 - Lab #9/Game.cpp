/*
	Name: Robert Wickliffe
	Description: Create a game of Tic-Tac-Toe.
	Section: CECS 130-01A
	Date: April 1, 2022
*/

#include "Game.h"

int Random(int max)
{
	return rand() % max;
};

Game::Game(int size)
{
	// Reset member variables
	this->turn = NONE;
	this->team = NONE;
	this->size = size;
	this->occupied = 0;
	
	// Create new board
	this->board = new Tile*[size];

	for (int i = 0; i < size; ++i)
		this->board[i] = new Tile[size];

	// Loop through tiles and set adjacent tiles
	for (int i = 0; i < this->size; ++i)
	{
		for (int v = 0; v < this->size; ++v)
		{
			this->board[i][v].tl = this->IsValid(i - 1, v - 1) ? &this->board[i - 1][v - 1] : NULL;
			this->board[i][v].t = this->IsValid(i - 1, v) ? &this->board[i - 1][v] : NULL;
			this->board[i][v].tr = this->IsValid(i - 1, v + 1) ? &this->board[i - 1][v + 1] : NULL;
			this->board[i][v].r = this->IsValid(i, v + 1) ? &this->board[i][v + 1] : NULL;
			this->board[i][v].br = this->IsValid(i + 1, v + 1) ? &this->board[i + 1][v + 1] : NULL;
			this->board[i][v].b = this->IsValid(i + 1, v) ? &this->board[i + 1][v] : NULL;
			this->board[i][v].bl = this->IsValid(i + 1, v - 1) ? &this->board[i + 1][v - 1] : NULL;
			this->board[i][v].l = this->IsValid(i, v - 1) ? &this->board[i][v - 1] : NULL;
		};
	};

	// Reset the board
	this->Reset();
};

Game::~Game()
{
	// Free allocated rows
	for (int i = 0; i < this->size; ++i)
		delete this->board[i];

	// Free board columns
	delete this->board;
};

void Game::Begin()
{
	// Reset the board
	this->Reset();

	// User's team
	char team = ' ';

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
	this->team = team == 'x' ? X : O;

	// Choose a random team to start first
	while (this->turn == NONE)
		this->turn = teams[Random(3)];

	// Display the board and print who has first move
	this->Display();

	std::cout << "Team " << (this->turn == X ? 'X' : 'O') << " has the first move." << std::endl;

	// Make current team take their turn
	this->DoTurn();
};

void Game::DoTurn()
{
	// Check if the game has a winner
	if (this->HasWinner())
		return;

	// If it is currently the user's turn else have the AI team make a move
	if (this->turn == this->team)
	{
		// Storage for user move
		char move[3] = { 'z', '9', '\0' };

		// Request the user to enter a move
		std::cout << "Please enter a move ( Ex. B2 ): ";

		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::cin.get(move, 3);

		// Get the corresponding row on board
		int row = move[1] - '1';

		// Get corresponding column on board
		int col = tolower(move[0]) - 'a';

		// Check if space is on board and is not taken
		if (!this->IsValid(row, col) || !this->IsAvailable(row, col))
		{
			std::cout << "Invalid Move, " << (!this->IsValid(row, col) ? "This space does not exist." : "This space is already occupied.") << std::endl;
			this->DoTurn();
		};

		// Set board space and display board and move
		this->SetBoardSpace(row, col, this->turn);

		// Display the game board
		this->Display();
	}
	else
		this->ChooseBestMove();

	// Chnage the turn to the opposite team
	if (this->turn == O)
		this->turn = X;
	else
		this->turn = O;

	// Make current team take their turn
	this->DoTurn();
};	

void Game::ChooseBestMove()
{
	// AI team and player team
	Team* cur_team = &this->turn;
	Team* opp_team = &this->team;

	// Last free in tile in column, row, or diagonal with most matches and number of matches
	Tile* last_free = NULL;
	int matches = 0;

	// If none or a single tile is occupied, choose a random tile
	if (this->occupied == 0 || this->occupied == 1)
	{
		// Choose random space
		int row = Random(this->size);
		int col = Random(this->size);

		// Ensure tile space is available
		while (!this->IsAvailable(row, col))
		{
			row = Random(this->size);
			col = Random(this->size);
		};

		// Set board space to AI team
		this->SetBoardSpace(row, col, this->turn);

		// Return and Display the game board
		return this->Display();
	};

	// Loop through board columns
	for (int i = 0; i < this->size; ++i)
	{
		// Current tile space in row, last free tile, and matches in row for teams
		Tile* cur_in_col = &this->board[0][i];
		Tile* last_free_col = NULL;

		int in_col = 0;
		int opp_in_col = 0;

		// Loop through tiles in column
		while (cur_in_col != NULL)
		{
			// If current column is first or last
			if (i == 0 || i == (this->size - 1))
			{
				// Current tile space in row, last free tile, and matches in row for teams
				Tile* cur_in_row = cur_in_col;
				Tile* last_free_row = NULL;

				int in_row = 0;
				int opp_in_row = 0;

				// Loop through tiles in row
				while (cur_in_row != NULL)
				{
					// Increment or set respective variables based on team
					if (cur_in_row->team == *cur_team)
						in_row++;
					else if (cur_in_row->team == *opp_team)
						opp_in_row++;
					else
						last_free_row = cur_in_row;

					// Get next tile to right in row
					cur_in_row = cur_in_row->r;
				};

				// If AI matches in row is greater than player matches
				if (in_row > opp_in_row || in_row == (this->size - 1))
				{
					// If row AI matches is greater than current greatest matches
					if (last_free_row != NULL && in_row > matches || in_row == (this->size - 1))
					{
						matches = in_row;
						last_free = last_free_row;
					};
				}
				else
				{
					// If row player matches is greater than current greatest matches
					if (last_free_row != NULL && opp_in_row > matches)
					{
						matches = opp_in_row;
						last_free = last_free_row;
					};
				};

				// If current tile is first in first or last column ( diagonal match possible )
				if (cur_in_col == &this->board[0][0] || cur_in_col == &this->board[0][this->size - 1])
				{
					// Current tile space in diagonal, last free tile, and matches in diagonal for teams
					Tile* cur_in_diag = cur_in_col;
					Tile* last_free_diag = NULL;

					int in_diag = 0;
					int opp_in_diag = 0;

					// Loop through tiles in diagonal
					while (cur_in_diag != NULL)
					{
						// Increment or set respective variables based on team
						if (cur_in_diag->team == *cur_team)
							in_diag++;
						else if (cur_in_diag->team == *opp_team)
							opp_in_diag++;
						else
							last_free_diag = cur_in_diag;

						// Get next tile in diagonal
						cur_in_diag = (cur_in_col == &this->board[0][0] ? cur_in_diag->br : cur_in_diag->bl);
					};

					// If AI matches in diagonal is greater than player matches
					if (in_diag > opp_in_diag || in_diag == (this->size - 1))
					{
						// If diagonal AI matches is greater than current greatest matches
						if (last_free_diag != NULL && in_diag > matches || in_diag == (this->size - 1))
						{
							matches = in_diag;
							last_free = last_free_diag;
						};
					}
					else
					{
						// If diagonal player matches is greater than current greatest matches
						if (last_free_diag != NULL && opp_in_diag > matches)
						{
							matches = opp_in_diag;
							last_free = last_free_diag;
						};
					};
				};
			};

			// Increment or set respective variables based on team
			if (cur_in_col->team == *cur_team)
				in_col++;
			else if (cur_in_col->team == *opp_team)
				opp_in_col++;
			else
				last_free_col = cur_in_col;

			// Get next tile in column
			cur_in_col = cur_in_col->b;
		};

		// If AI matches in column is greater than player matches
		if (in_col > opp_in_col || in_col == (this->size - 1))
		{
			// If column AI matches is greater than current greatest matches
			if (last_free_col != NULL && in_col > matches || in_col == (this->size - 1))
			{
				matches = in_col;
				last_free = last_free_col;
			};
		}
		else
		{
			// If column player matches is greater than current greatest matches
			if (last_free_col != NULL && opp_in_col > matches)
			{
				matches = opp_in_col;
				last_free = last_free_col;
			}
		};
	};

	// Set the team of last best free tile to AI team and increment occupied tiles
	last_free->team = this->turn;
	this->occupied++;

	// Return and Display the game board
	return this->Display();
};

void Game::Display()
{
	printf("   ");
	
	// Print corresponding board letter headers
	for (int i = 0; i < this->size; ++i)
	{
		if (i != (this->size - 1))
			printf(" %c  ", toupper('a' + i));
		else
			printf(" %c  \n", toupper('a' + i));
	};

	// Print corresponding rows numbers and moves
	for (int i = 0; i < this->size; ++i)
	{
		printf("%d |", i + 1);

		for (int v = 0; v < this->size; ++v)
		{
			if (v != (this->size - 1))
				printf(" %c |", this->AsChar(i, v));
			else
				printf(" %c |\n", this->AsChar(i, v));
		};
	};

	printf("\n");
};

Team Game::At(short row, short col)
{
	// Check if board space is on board
	if (!this->IsValid(row, col))
		return NONE;

	return this->board[row][col].team;
};

char Game::AsChar(short row, short col)
{
	// Check if board space is on board
	if (!this->IsValid(row, col))
		return ' ';

	// Return symbol in array corresponding to team enum value
	return symbols[(int)this->At(row, col)];
};

bool Game::IsValid(short row, short col)
{
	// Return if board space is within bounds of # of rows and columns
	return (row >= 0) && (row < this->size) && (col >= 0) && (col < this->size);
};

bool Game::IsAvailable(short row, short col)
{
	// Return if space is valid and no team has made move on space
	return (this->IsValid(row, col)) && (this->At(row, col) == NONE);
};

bool Game::HasWinner()
{
	// Loop through board columns
	for (int i = 0; i < this->size; ++i)
	{
		// Current tile space in column, team of column, and matches in column
		Tile* cur_in_col = &this->board[0][i];
		Team* cur_team_col = &this->board[0][i].team;
		int in_col = 0;

		// Loop through tiles in column
		while (cur_in_col != NULL)
		{
			// If current column is first or last
			if (i == 0 || i == (this->size - 1))
			{
				// Current tile space in row, team of row, and matches in row
				Tile* cur_in_row = cur_in_col;
				Team* cur_team_row = &cur_in_col->team;
				int in_row = 0;

				// If current tile in row isnt NULL and tile team matches row team
				while (cur_in_row != NULL && cur_in_row->team == *cur_team_row && *cur_team_row != NONE)
				{
					// Get next tile in row and increment row matches
					cur_in_row = cur_in_row->r;
					in_row++;
				};

				// If match requirement is met
				if (in_row == this->size)
				{
					std::cout << "Team " << (*cur_team_row == X ? "X" : "O") << " wins, they matched " << this->size << " in a row!" << std::endl << std::endl;
					return true;
				};

				// If current tile is first in first or last column ( diagonal match possible )
				if (cur_in_col == &this->board[0][0] || cur_in_col == &this->board[0][this->size - 1])
				{
					// Current tile space in diagonal, team of diagonal, and matches in diagonal
					Tile* cur_in_diag = cur_in_col;
					Team* cur_team_diag = &cur_in_col->team;
					int in_diag = 0;

					// If current tile in diagonal isnt NULL and tile team matches diagonal team
					while (cur_in_diag != NULL && cur_in_diag->team == *cur_team_diag && *cur_team_diag != NONE)
					{
						// Get next tile in diagonal and increment diagonal matches
						cur_in_diag = (cur_in_col == &this->board[0][0] ? cur_in_diag->br : cur_in_diag->bl);
						in_diag++;
					};

					// If match requirement is met
					if (in_diag == this->size)
					{
						std::cout << "Team " << (*cur_team_diag == X ? "X" : "O") << " wins, they matched " << this->size << " diagonally!" << std::endl << std::endl;
						return true;
					};
				};
			};

			// If current tile in column isnt NULL and tile team matches column team
			if (cur_in_col->team == *cur_team_col && *cur_team_col != NONE)
				in_col++;

			// Get next tile in column
			cur_in_col = cur_in_col->b;
		};

		// If match requirement is met
		if (in_col == this->size)
		{
			std::cout << "Team " << (*cur_team_col == X ? "X" : "O") << " wins, they matched " << this->size << " in a column!" << std::endl << std::endl;
			return true;
		};
	};

	if (this->occupied == pow(this->size, 2))
	{
		std::cout << "Nobody wins, all tiles have been occupied." << std::endl << std::endl;
		return true;
	};

	return false;
}

bool Game::SetBoardSpace(short row, short col, Team team)
{
	// Check if board space is on board and not taken
	if (!this->IsValid(row, col) || !this->IsAvailable(row, col))
		return false;

	// Set team at board space to supplied team
	this->board[row][col].team = team;
	this->occupied++;

	return true;
};

void Game::Reset()
{
	// Loop through row and columns and set team to NONE
	for (int i = 0; i < this->size; ++i)
		for (int v = 0; v < this->size; ++v)
			this->board[i][v].team = NONE;

	this->occupied = 0;
};
