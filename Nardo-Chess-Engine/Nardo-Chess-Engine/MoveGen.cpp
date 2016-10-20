// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Generates all moves within the chess game.

#include "stdafx.h"

// Arrays used for movement

// This array stores which pieces can "slide"
// Queen	Bishop	Rook can slide
// King		Knight		 can not slide
bool slide[5] = { 0, 1, 1, 1, 0 };	

// This array stores how many directions each piece can move in
// Pieces can either move in 8 directions or 4
// Bishops	Rooks		  can only move in 4
// Queens	Knights	Kings can only move in 8
int routes[5] = { 8, 8, 4, 4, 8 };

// This array stores the incremental updaters for each direction
// Queens	Kings	can move in any direction
// Bishops	Rooks	can move in diagonals/lines
// Knights			can move in an L-shape pattern (represented by hard coded values)
int route[5][8] = {
	{  SW,   S,  SE,   W,   E,  NW,   N,  NE }, // KING
    {  SW,   S,  SE,   W,   E,  NW,   N,  NE },	// QUEEN
    {   S,   W,   E,  N                      },	// ROOK
    {  SW,  SE,  NW,  NE					 },	// BISHOP
    { -17, -15, -10,  -6,   6,  10,  15,  17 }	// KNIGHT
};	

// Variables
int movecount = 0;
vector<Move> m;

// Sets the board b's moves to the temporary vector m
void setmoves(Board* b)
{
	b->mlist.clear();
	for (Move elem : m)
		b->mlist.push_back(elem);
}

// Add flag if last piece that moved was pawn
// Possible en passent
// *Add castling*
// Returns movecount 
int mgen(Board* b)
{
	// Set movecount and movelist to empty
	movecount = 0;
	m.clear();

	// Iterate through entire board
	for (S8 sq = 0; sq < 64; sq++) {

		// This stores the last square position
		S8 lsq = sq;

		// Only generate moves for current side
		if (b->c[sq] == b->stm) {
			
			// If the piece is a pawn
			if (b->p[sq] == PAWN) {
				gpmove(sq, b);
				gpcapt(sq, b);
			}
			// Other pieces
			else {
				// For loop: incrementally updating direction
				for (int dir = 0; dir < routes[b->p[sq]]; dir++) {
					// For loop: infinite and sets initial pos
					for (S8 pos = sq;;) {

						// Update position
						pos += route[b->p[sq]][dir];

						// Break if position does not exist
						if (!IS_SQ(pos)) break;

						// This solves a piece moving from h3 to a4
						// If the column from one step is over 1 away
						// This means they jumped across the board
						// Do not generate these moves
						if ((COL(pos) > COL(lsq)+1) || (COL(pos) < COL(lsq)-1)) break;

						// Generate moving to an empty square
						if (b->p[pos] == PIECE_EMPTY) {
							gmove(sq, pos, b->c[sq], false);
							movecount++;
						}
						// Generate a capture move
						// Break since you can no longer move in that direction
						else if (b->c[pos] != b->stm) {
							gmove(sq, pos, b->c[sq], true);
							movecount++;
							break;
						}
						// This means you are trying to capture one of your own pieces
						else break;

						// Break if a piece cannot slide
						// Queens slide, Kings do not
						if (!slide[b->p[sq]]) break;

						// Save the last square for updating purposes
						lsq = pos;
					}
				}
			}
		}
	}
	setmoves(b);
	return movecount;
}

// This function generates a move and pushes it into the movelist
void gmove(int f, int t, int pc, int capture)
{
	Move temp = Move(f, t, pc, capture);
	m.push_back(temp);
}

// This function determines pawn moves to generate
// Then uses gmove to generate the pawn moves
void gpmove(int sq, Board* b)
{
	// White moves 
	if (b->stm == WHITE) {

		// Move forward one
		if (IS_SQ(sq + N) && b->p[sq + N] == PIECE_EMPTY) {
			gmove(sq, sq + N, WHITE, false);

			// Move forward two
			if (ROW(sq) == 1 && b->p[sq+N] == PIECE_EMPTY && b->p[sq+N+N] == PIECE_EMPTY)
				gmove(sq, sq + N + N, WHITE, false);
		}
	}

	// Black moves
	else {

		// Move forward one
		if (IS_SQ(sq+S) && b->p[sq+S] == PIECE_EMPTY) {
			gmove(sq, sq+S, BLACK, false);

			// Move forward two
			if (ROW(sq) == 6 && b->p[sq+S] == PIECE_EMPTY && b->p[sq+S+S] == PIECE_EMPTY)
				gmove(sq, sq+S+S, BLACK, false);
		}
	}
}

// This function determines pawn captures
// If there are captures, gmove is used to generate them
void gpcapt(int sq, Board* b)
{
	// White moves
	if (b->stm == WHITE) {

		// Checks to see if the square exists and contains a black piece
		// This also solves a piece moving from h3 to a4
		if ((IS_SQ(sq+NW)) && (b->c[sq+NW] == BLACK) &&
			(!(COL(sq+NW) > COL(sq) + 1)) && 
			(!(COL(sq+NW) < COL(sq) - 1))) {
			gmove(sq, sq+NW, WHITE, true);
		}
		// Checks to see if the square exists and contains a black piece
		// This also solves a piece moving from h3 to a4
		if ((IS_SQ(sq+NE)) && (b->c[sq+NE] == BLACK) &&
			(!(COL(sq+NE) > COL(sq) + 1)) && 
			(!(COL(sq+NE) < COL(sq) - 1))) {
			gmove(sq, sq+NE, WHITE, true);
		}

		// ADD EN PASSENT FLAG IN MOVE


		//// Checks for en passent 
		//// Checks to see if the square exists and contains a black piece
		//// This also solves a piece moving from h3 to a4
		//if (IS_SQ(sq+W) && b->c[sq] == BLACK &&
		//	!(COL(sq+W) > COL(sq) + 1) && 
		//	!(COL(sq+W) < COL(sq) - 1)) {
		//	gmove(sq, sq+W, WHITE, true);
		//}
		//// Checks for en passent 
		//// Checks to see if the square exists and contains a black piece
		//// This also solves a piece moving from h3 to a4
		//if (IS_SQ(sq+E) && b->c[sq] == BLACK &&
		//	!(COL(sq+E) > COL(sq) + 1) && 
		//	!(COL(sq+E) < COL(sq) - 1)) {
		//	gmove(sq, sq+E, WHITE, true);
		//}
	}
	// Black moves
	else {

		// Checks to see if the square exists and contains a black piece
		// This also solves a piece moving from h3 to a4
		if ((IS_SQ(sq+SW)) && (b->c[sq+SW] == WHITE) &&
			(!(COL(sq+SW) > COL(sq) + 1)) && 
			(!(COL(sq+SW) < COL(sq) - 1))) {
			gmove(sq, sq+SW, BLACK, true);
		}
		// Checks to see if the square exists and contains a black piece
		// This also solves a piece moving from h3 to a4
		if ((IS_SQ(sq+SE)) && (b->c[sq+SE] == WHITE) &&
			(!(COL(sq+SE) > COL(sq) + 1)) && 
			(!(COL(sq+SE) < COL(sq) - 1))) {
			gmove(sq, sq+SE, BLACK, true);
		}

		// ADD EN PASSENT FLAG IN MOVE


		//// Checks for en passent 
		//// Checks to see if the square exists and contains a black piece
		//// This also solves a piece moving from h3 to a4
		//if (IS_SQ(sq+W) && b->c[sq] == BLACK &&
		//	!(COL(sq+W) > COL(sq) + 1) && 
		//	!(COL(sq+W) < COL(sq) - 1)) {
		//	gmove(sq, sq+W, BLACK, true);
		//}
		//// Checks for en passent 
		//// Checks to see if the square exists and contains a black piece
		//// This also solves a piece moving from h3 to a4
		//if (IS_SQ(sq+E) && b->c[sq] == WHITE &&
		//	!(COL(sq+E) > COL(sq) + 1) && 
		//	!(COL(sq+E) < COL(sq) - 1)) {
		//	gmove(sq, sq+E, BLACK, true);
		//}
	}
}