// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Contains functions to check for game rules such as check.

#include "stdafx.h"

// This array stores the incremental updaters for diagonals
int cdiagonal[4] = { NW, NE, SW, SE };

// This array stores the incremental updaters for rows/cols
int crowcol[4]   = { N, S, E, W };

// This array stores the incremental updaters for knights
int cknight[8]   = { -17, -15, -10, -6, 6, 10, 15, 17 };

// NOT IMPLEMENTED YET
// Determines if the game is over or not
bool game_over(Board* brd)
{
	return false;
}

// Determines if the current side is in check
bool in_check(Board* brd)
{
	// Iterate through the entire board
	for (int sq = 0; sq < 64; sq++) {

		// Find current side's king position
		if (brd->p[sq] == KING && brd->c[sq] == brd->stm) {

			// Used for directional increment
			int incr = 0;

			// *** Knight Checks ***
			// Checks along knight squares
			for (int route = 0; route < 8; route++) {

				if (!IS_SQ(sq+cknight[route])) break;
				if (brd->c[sq+cknight[route]] == brd->stm) break;
				if (brd->c[sq+cknight[route]] == ALT(brd->stm)) {

					if (brd->p[sq+cknight[route]] == KNIGHT) 
						return true;
				}
			}

			// *** Diagonal Checks ***
			// Checks along four diagonals
			// Checks in each direction seven squares
			for (int route = 0; route < 4; route++) {
				for (int dir = 1; dir < 8; dir++) {

					// This int is the aditional amount to add to sq
					// Takes into account which diagonal you are checking down
					// Takes into account how far along diagonal you are checking
					incr = sq + (cdiagonal[route]*dir);

					if (!IS_SQ(incr)) break;
					if (brd->c[incr] == brd->stm) break;
					if (brd->c[incr] == ALT(brd->stm)) {

						if (brd->p[incr] == QUEEN ||
							brd->p[incr] == BISHOP ||
							brd->p[incr] == PAWN) {
							
							// Extra checks needed for Pawn
							if (brd->p[incr] == PAWN) {

								// Incr is where the pawn is, Sq is where the king is

								// Checks to make sure it can't check from more than one sq away
								if ((COL(incr) > COL(sq)+1) || (COL(incr) < COL(sq)-1)) break;

								// Checks to make sure the black king is one row ahead of pawn
								else if (brd->c[incr] == WHITE) 
									if (ROW(incr) != ROW(sq)-1) break; 
								
								// Checks to make sure the white king is one row before pawn
								else if (brd->c[incr] == BLACK) 
									if (ROW(incr) != ROW(sq)+1) break; 
								
							}
							
							return true;
						}
					}
				}
			}

			// *** Row & Col Checks ***
			// Checks along two rows and two columns
			// Checks in each direction seven squares
			for (int route = 0; route < 4; route++) {
				for (int dir = 1; dir < 8; dir++) {

					// This int is the aditional amount to add to sq
					// Takes into account which row/col you are checking down
					// Takes into account how far along row/col you are checking
					incr = sq + (crowcol[route]*dir);

					if (!IS_SQ(incr)) break;
					if (brd->c[incr] == brd->stm) break;
					if (brd->c[incr] == ALT(brd->stm)) {

						if (brd->p[incr] == QUEEN ||
							brd->p[incr] == ROOK) 
							return true;
					}
				}
			}
		}
	}

	return false;
}