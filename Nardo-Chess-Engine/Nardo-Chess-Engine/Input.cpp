// Author: Dante Nardo
// Last Modified: 10/20/16
// Purpose: Handles all manual user input via console to simulate chess games.

#include "stdafx.h"

// Receives and returns valid input
// Returns a pointer to a move struct
Move get_input(const int color, Board* brd)
{
	// Create string 
	string from = "default";
	string to = "default";

	// Create boolean to contain capture value
	bool cap = false;

	// Create numbers to convert to spots on board
	int	f = 0;
	int t = 0;

	// Run until we have valid input
	while (true) {

		// Try to get valid user input
		try {
			// Enter square to move from
			cout << "\nEnter square to move piece from.\n";
			cout << "Example: A1\n";
			cout << "From: ";
			cin >> from;

			// Enter square to move to
			cout << "\n\nEnter square to move piece to.\n";
			cout << "Example: A1\n";
			cout << "To: ";
			cin >> to;

			// If the input is valid, create a move pointer and return it
			// The 'return m;' line is the only possible way to break loop
			if (val_input(from, to, color, cap, f, t, brd)) {
				Move m = Move(f, t, color, cap);
				return m;
			}
		}

		// Catch bad input and reset stream
		catch (istream::failure e) {
			cin.clear(); // Clear the flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nINVALID_INPUT\n";
		}
	}
}

// Receives the input for the move
// Returns true if valid input
bool val_input(const string f, const string t, const int c, 
				bool &cp, int &outf, int &outt, Board* brd)
{
	// If you can convert input
	// If you're moving and capturing correct color
	if (cnv_input(f, outf) &&
		cnv_input(t, outt) &&
		brd->c[outf] == c  &&
		brd->c[outt] != c) {

		// If the square moving to is not color empty
		// Then it must be the opposite color
		// This means it is a capture move - make cp true
		if (brd->c[outt] != COLOR_EMPTY)
			cp = true;

		return true;
	}
	// You cannot convert input
	// Return false - nonvalid input
	else {
		cout << "\nINVALID INPUT\n";
		return false;
	}
}

// Receives the input string and a reference variable
// The out reference variable is changed to the input
// Returns true if it can convert
bool cnv_input(string inp, int &out)
{
	// If input isn't two (valid input == 
	if (inp.size() != 2)
		return false;

	// Isolate letter, all caps
	char letter = toupper(inp[0]);

	// Generate row and col integers
	// Make char an int: '2' - '0' = 2
	// Subtract one since 2nd elemtn = 1 in array
	// Multiply by 8 for row value
	int row = ((inp[1] - '0')-1) * 8; 
	int col = 0;

	// Determins int col's value from letter
	switch (letter) {
	case 'A':
		col = 0;
		break;
	case 'B':
		col = 1;
		break;
	case 'C':
		col = 2;
		break;
	case 'D':
		col = 3;
		break;
	case 'E':
		col = 4;
		break;
	case 'F':
		col = 5;
		break;
	case 'G':
		col = 6;
		break;
	case 'H':
		col = 7;
		break;
	default:
		return false;
	}

	// If this square is on the board
	// Convert input and return true
	if (IS_SQ(col + row)) {
		out = col + row;
		return true;
	}
	else
		return false;
}