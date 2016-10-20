// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Handles control and flow over entire game.

#include "stdafx.h"
#include "Game.h"

// Include global board variable
Board gbrd;

// Constructor and Deconstructor
Game::Game()
{
	// Initialize everything
	gbrd = Board();
}

Game::~Game()
{
	delete &gbrd;
}

// This is the only function called
// This function 
void Game::play()
{
	// While the game isn't over
	while (true) {

		// Draw board
		drawb(gbrd);

		// Generate moves
		mgen(&gbrd);

		// Loop until they make a valid move
		while (true) {

			// Receive input - Generate move
			Move cm = get_input(cc, &gbrd);

			// If you can move, make the move
			if (cmove(&cm, &gbrd)) {
				mmove(&cm, &gbrd);

				// If the current side is in check, move was invalid
				if (in_check(&gbrd)) {
					umove(&cm, &gbrd);
					cout << "\nInvalid Move\n";
				}

				// Reset and alternate turn
				else {
					reset();
					break;
				}
			}
			// If this is reached, the input is invalid
			else cout << "\nInvalid Move\n";
		}

		

		// Checks to see if the game is over
		if (game_over(&gbrd)) {
			cout << "\nGAME OVER" << endl;
			cout << cc << " wins!" << endl;
			break;
		}
	}
}

// These functions handle game state changes
bool Game::reset()
{
	// Alternate the turn at the end
	alternate();

	return true;
}

void Game::alternate()
{
	cc = (cc == WHITE) ? BLACK: WHITE;
	gbrd.stm = cc;
}