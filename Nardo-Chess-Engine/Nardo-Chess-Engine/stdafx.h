// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Defines the functions and structures of the chess engine.

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "Math.h"

using namespace std;

// ================================================================================
// ============================== ENUMERATORS =====================================
// ================================================================================

// Square enumerators
enum esquare {
	A1 =  0, B1, C1, D1, E1, F1, G1, H1,
	A2 =  8, B2, C2, D2, E2, F2, G2, H2,
	A3 = 16, B3, C3, D3, E3, F3, G3, H3,
	A4 = 24, B4, C4, D4, E4, F4, G4, H4,
	A5 = 32, B5, C5, D5, E5, F5, G5, H5,
	A6 = 40, B6, C6, D6, E6, F6, G6, H6,
	A7 = 48, B7, C7, D7, E7, F7, G7, H7,
	A8 = 56, B8, C8, D8, E8, F8, G8, H8
};

// Piece Enumerators
enum epiece
{
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
	PIECE_EMPTY
};

// Color Enumerators
enum ecolor
{
	WHITE,
	BLACK,
	COLOR_EMPTY
};


// ================================================================================
// ============================== STRUCTURES ======================================
// ================================================================================


// Move structure
struct Move
{
	S8 fr    = 0;			// Square you came from
	S8 to    = 1;			// Square you are going to
	char pc  = COLOR_EMPTY;	// The color of the moving piece
	bool cap = false;		// Whether or not this move is a capture

	Move(int f, int t, char c, bool capture) {
		fr  = f;
		to  = t;
		pc  = c;
		cap = capture;
	}
};

// Board Structure
struct Board
{
	S8 p[64]; // One dimensional board of type unsigned __int8: pieces
	S8 c[64]; // One dimensional board of type unsigned __int8: color

	// Vector of moves that stores current moves
	vector<Move> mlist;

	// Capture info: save so we can undo moves
	int cp = PIECE_EMPTY; // capture piece
	int cc = COLOR_EMPTY; // capture color

	// Side to move
	int stm = WHITE;

	// Constructor
	Board()
	{
		// Instantiate board as empty
		for (int i = 0; i < 64; i++) {
			p[i] = PIECE_EMPTY;
			c[i] = COLOR_EMPTY;
		}

		// Generate white pawns
		for (int j = 8; j < 16; j++) {
			p[j] = PAWN;
			c[j] = WHITE;
		}

		// Place white pieces and colors
		p[0] = ROOK;	c[0] = WHITE;
		p[1] = KNIGHT;	c[1] = WHITE;
		p[2] = BISHOP;	c[2] = WHITE;
		p[3] = QUEEN;	c[3] = WHITE;
		p[4] = KING;	c[4] = WHITE;
		p[5] = BISHOP;	c[5] = WHITE;
		p[6] = KNIGHT;	c[6] = WHITE;
		p[7] = ROOK;	c[7] = WHITE;

		// Generate black pawns
		for (int k = 48; k < 56; k++) {
			p[k] = PAWN;
			c[k] = BLACK;
		}

		// Place black pieces and colors
		p[56] = ROOK;	c[56] = BLACK;
		p[57] = KNIGHT;	c[57] = BLACK;
		p[58] = BISHOP;	c[58] = BLACK;
		p[59] = QUEEN;	c[59] = BLACK;
		p[60] = KING;	c[60] = BLACK;
		p[61] = BISHOP;	c[61] = BLACK;
		p[62] = KNIGHT;	c[62] = BLACK;
		p[63] = ROOK;	c[63] = BLACK;
	}
};

// Create a global variable for the board
// This let's the board be accessed wherever we need it
extern Board gbrd;

// Hash structure
struct hashTable 
{
	// Add castling
	int zobrist[6][2][64]; // Piece, Color, Squares
	map<int, Move> htable;
};

// Create a global variable for the hashtable
// This let's the hashtable be accessed wherever we need it
extern hashTable ht;

// Movement structures
extern bool slide[5];
extern int	route[5][8];
extern int	routes[5];

// Rule structures
extern int cdiagonal[4];
extern int crowcol[4];
extern int cknight[8];

// ================================================================================
// ============================== FUNCTIONS =======================================
// ================================================================================

// Move Functions
void mmove(Move* m, Board* brd); // make  move
void umove(Move* m, Board* brd); // undo  move
bool cmove(Move* m, Board* brd); // can   move
bool emove(Move* m1, Move* m2);	 // equal move

// MoveGen Functions
void setmoves(Board* b);
int  mgen(Board* b);
void gmove(int f, int t, int pc, int capture);
void gpmove(int sq, Board* b);
void gpcapt(int sq, Board* b);

// Input Functions
Move get_input(const int color, Board* brd);
bool val_input(const string f, const string t, const int c, bool &cp, int &outf, int &outt, Board* brd);
bool cnv_input(string inp, int &out);

// Rule Functions
bool game_over(Board* brd);
bool in_check(Board* brd);

// Draw Functions
void drawb(Board brd);