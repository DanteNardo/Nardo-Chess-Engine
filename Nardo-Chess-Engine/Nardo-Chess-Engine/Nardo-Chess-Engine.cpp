// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: The main function that instantiates and runs the chess game.

// Nardo-Chess-Engine.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Game.h"

int main()
{
	Game chess = Game();
	chess.play();

	return 0;
}