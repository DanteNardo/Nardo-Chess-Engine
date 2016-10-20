// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Handles all board movement within the game.

#include "stdafx.h"

// Board Movement, make and undo moves
void mmove(Move* m, Board* brd)
{
	// If capture, save capture for (possible) undo
	if (m->cap) {
		brd->cp = brd->p[m->to];
		brd->cc = brd->c[m->to];
	}
	// Else, clear possible capture data
	else {
		brd->cp = PIECE_EMPTY;
		brd->cc = COLOR_EMPTY;
	}

	// Move piece to new square
	brd->p[m->to] = brd->p[m->fr];
	brd->c[m->to] = brd->c[m->fr];

	// Delete old square data
	brd->p[m->fr] = PIECE_EMPTY;
	brd->c[m->fr] = COLOR_EMPTY;
}

void umove(Move* m, Board* brd)
{
	brd->p[m->to] = brd->p[m->fr];
	brd->c[m->to] = brd->c[m->fr];

	brd->p[m->fr] = brd->cp;
	brd->c[m->fr] = brd->cc;
}

// Returns true if you can move
bool cmove(Move* m, Board* brd)
{
	// Iterate through movelist
	for (Move bm : brd->mlist) {

		// If two moves are equal: return true
		if (emove(m, &bm))
			return true;
	}

	// If none of the moves were equal: return false
	return false;
}

// Returns true if the two moves are equal
bool emove(Move* m1, Move* m2)
{
	if (m1->cap != m2->cap)	return false;
	if (m1->fr  != m2->fr)  return false;
	if (m1->to  != m2->to)  return false;
	if (m1->pc  != m2->pc)  return false;
	
	return true;
}