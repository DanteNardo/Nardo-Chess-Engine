// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Defines mathematical functions and variables necessary for the chess engine.

#pragma once

// These are defined int types for the game
#define S8 unsigned __int8 // square 8 bit

// These are used for moving throughout the board
#define N	8	// North
#define S  -8	// South
#define E	1	// East
#define W  -1	// West

#define NW (N + W)	// Northwest
#define NE (N + E)	// Northeast
#define SW (S + W)	// Southwest
#define SE (S + E)	// Southeast

// Create square (int) from row and col
#define SET_SQ(row,col) (row * 8 + col)

// Determine if a square exists on the board
#define IS_SQ(x)  ((x >= 0) && (x < 64)) ? (1) : (0)

// Get column from square
#define COL(sq)  ((sq) % 8)

// Get row from square
#define ROW(sq)  ((sq) / 8)

// Determine if two squares are on the same column
#define SAME_COL(sq1,sq2) ((COL(sq1) == COL(sq2)) ? (1) : (0) )

// Determine if two squares are on the same row
#define SAME_ROW(sq1,sq2) ((ROW(sq1) == ROW(sq2)) ? (1) : (0) )

// Switches WHITE to BLACK and BLACK to WHITE
#define ALT(stm) ((stm == WHITE) ? (BLACK) : (WHITE))