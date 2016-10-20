// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Handles control and flow over entire game.

#pragma once
class Game
{
public:

	// Constructor and deconstructor
	Game();
	~Game();

	// Inside of this function, everything happens
	void play();

	// This function resets variables for the next turn
	// Returns a boolean true if reset is successful else false
	bool reset();

	// Alternates between player's turns
	void alternate();

private:

	int cc = WHITE; // currentColor
};

