// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Prints the game to the console.

#include "stdafx.h"

void drawb(Board b)
{
	cout << endl;

	// Print out pieces
	for (int row = 7; row >= 0; row--) {
		for (int col = 0; col < 8; col++) {
			int sq = SET_SQ(row, col);
			
			switch (b.p[sq]) {
			case PIECE_EMPTY:
				cout << "0 ";
				break;
			case KING:
				cout << "K ";
				break;
			case QUEEN:
				cout << "Q ";
				break;
			case ROOK:
				cout << "R ";
				break;
			case BISHOP:
				cout << "B ";
				break;
			case KNIGHT:
				cout << "N ";
				break;
			case PAWN:
				cout << "P ";
				break;
			default:
				cout << "ERROR";
				break;
			}
		}
		cout << endl;
	}

	cout << endl;

	// Print out colors
	for (int row = 7; row >= 0; row--) {
		for (int col = 0; col < 8; col++) {
			int sq = SET_SQ(row, col);
			
			switch (b.c[sq]) {
			case COLOR_EMPTY:
				cout << "0 ";
				break;
			case WHITE:
				cout << "W ";
				break;
			case BLACK:
				cout << "B ";
				break;
			default:
				cout << "E";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}