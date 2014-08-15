// main.cpp - Othello program main entry point
// Written by Paul Jang

// including various necessary files
#include <iostream>
#include <vector>
#include <math.h>
#include "Player.h"

using namespace std;

#define ROWS	8	 // standard size for rows
#define COLS	8	 // standard size for columns

// initiates the game with an empty board and four pieces in the center
// Parameter : (empty) - empty char array representing the game board
void initiate(char empty[ROWS][COLS])
{
	// nested for loops to traverse all coordinates
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COLS; j++)
		{
			empty[i][j] = '-';
		}
	}

	// four pieces are always set at the beginning
	empty[3][3] = empty[4][4] = 'w';
	empty[3][4] = empty[4][3] = 'b';
}


// displays the current game board
// Parameter : (gameBoard) - char array representing the game board
void displayBoard(const char gameBoard[ROWS][COLS])	
{
	// spaces for neat formatting
	cout << endl << "  ";
	
	// creates empty column spaces
	for(int c=0; c<COLS; c++)
	{
		cout << c << " ";
	}
	cout << endl;

	// traverses the board and adds appropriate spaces
	for(int r=0; r<ROWS; r++)
	{
		cout << r << " ";
		for(int c=0; c<COLS; c++)
		{
			cout << gameBoard[r][c] << ' ';
		}
		cout << endl;
	}
}


// outputs a list of viable moves to be made
// Parameters: (gameBoard) - char array representing the game board
// (legalRows + legalCols) - vectors representing legal row values and legal column values
// (disc) - char representing either white ('w') or black ('b')
void listMoves(char gameBoard[ROWS][COLS], vector<int>& legalRows, vector<int>& legalCols, char disc)	
{
	int rowD=0;	 // row increment around the current square
	int colD=0;	 // column increment around the current square
	int row=0;	 // current row index
	int col=0;	 // current column index
	int x=0;	 // row index while searching
	int y=0;	 // column index while searching
	char opponent;	// opponent char

	// assigns the opposite char as the opponent
	if(disc == 'w')
		opponent = 'b';
	else
		opponent = 'w';
	
	// traverses all rows and columns
	for(row=0; row<ROWS; row++)
	{
		for(col=0; col<COLS; col++)
		{
			// goes ahead if the space is not empty
			if(gameBoard[row][col] != '-')
				continue;
			// traverses all spaces around the current space
			for(rowD = -1; rowD <= 1; rowD++)
			{
				for(colD = -1; colD <= 1; colD++)
				{
					// makes sure we don't go outside the gameboard
					if(row+rowD <0 || row+rowD >= ROWS
						|| col+colD<0 || col+colD >= COLS
						|| (rowD == 0 && colD ==0))
					{
						continue;
					}
					
					// if a space around the current space is an opponent piece
					if((gameBoard[row+rowD][col+colD] == opponent))
					{
						// saves the x(row) and y(col) of the opposing space
						x = row + rowD;
						y = col + colD;
						
						// repeats
						for(;;)
						{
							// adds the appropriate increment
							x += rowD;
							y += colD;

							// breaks if we go outside the board
							if(x<0 || x>=ROWS || y<0 || y>=COLS)
								break;

							// breaks if we hit an empty space
							if(gameBoard[x][y] == '-')
								break;

							// adds the coordinates to the vectors if the space is a disc
							// of the current player
							if(gameBoard[x][y] == disc)
							{
								legalRows.push_back(row);
								legalCols.push_back(col);
								break;
							}
						}
					}
				}
			}
		}
	}

	// outputs a message if there are no viable moves
	if(legalRows.size() == 0)
	{
		cout << "The current player does not have a viable move...";
	}

	// outputs the list of viable moves
	else
	{
		cout << "The current player's viable moves are... " << endl;
		for(unsigned int i=0; i<legalRows.size(); i++)
		{
			cout << "Row : " << legalRows[i] << "   Column : " << legalCols[i] << endl;
		}
	}
}


// outputs a list of viable moves to be made for the AI
// exactly the same as listMoves but doesn't output the list of moves
// Parameters: (gameBoard) - char array representing the game board
// (legalRows + legalCols) - vectors representing legal row values and legal column values
// (disc) - char representing either white or black
void listMovesAI(char gameBoard[ROWS][COLS], vector<int>& legalRows, vector<int>& legalCols, char disc)	
{
	int rowD=0;	 // row increment around the current square
	int colD=0;	 // column increment around the current square
	int row=0;	 // current row index
	int col=0;	 // current column index
	int x=0;	 // row index while searching
	int y=0;	 // column index while searching
	char opponent;	// opponent char

	if(disc == 'w')
		opponent = 'b';
	else
		opponent = 'w';

	for(row=0; row<ROWS; row++)
	{
		for(col=0; col<COLS; col++)
		{
			if(gameBoard[row][col] != '-')
				continue;
			for(rowD = -1; rowD <= 1; rowD++)
			{
				for(colD = -1; colD <= 1; colD++)
				{
					if(row+rowD <0 || row+rowD >= ROWS
						|| col+colD<0 || col+colD >= COLS
						|| (rowD == 0 && colD ==0))
					{
						continue;
					}
					if((gameBoard[row+rowD][col+colD] == opponent))
					{
						x = row + rowD;
						y = col + colD;
						for(;;)
						{
							x += rowD;
							y += colD;
							if(x<0 || x>=ROWS || y<0 || y>=COLS)
								break;
							if(gameBoard[x][y] == '-')
								break;
							if(gameBoard[x][y] == disc)
							{
								legalRows.push_back(row);
								legalCols.push_back(col);
								break;
							}
						}
					}
				}
			}
		}
	}
	// *************************************************************
	// since this is for the AI, displaying the moves is unnecessary
	/*
	if(legalRows.size() == 0)
	{
		cout << "The current player does not have a viable move...";
	}
	else
	{
		cout << "The current player's viable moves are... " << endl;
		for(unsigned int i=0; i<legalRows.size(); i++)
		{
			cout << "Row : " << legalRows[i] << "   Column : " << legalCols[i] << endl;
		}
	}
	*/
}


// takes a coordinate and changes the board accordingly
// Parameters: (gameBoard) - char array representing the game board
// (row + col) - coordinate representing where the piece will be placed
// (color) - char representing the color of the piece being placed
void flipDiscs(char gameBoard[ROWS][COLS], int& row, int& col, char color)
{
	int rowD = 0;	// row increment
	int colD = 0;	// column increment
	int x = 0;		// current row index
	int y = 0;		// current column index
	char opponent;	// opponent color

	// assigns the opposing color
	if(color == 'w')
		opponent = 'b';
	else
		opponent = 'w';

	// changes the actual coordinate to the appropriate game piece
	gameBoard[row][col] = color;

	// Check all squares around the current square for opponent pieces
	for(rowD = -1; rowD <= 1; rowD++)
	{
		for(colD = -1; colD <= 1; colD++)
		{
			// continues only if we are still on the game board
			if(row+rowD <0 || row+rowD >= ROWS || col+colD<0 || col+colD >= COLS
				|| (rowD==0 && colD==0))
				continue;

			// keeps track if an opposing piece needs to be flipped
			if(gameBoard[row+rowD][col+colD] == opponent)
			{
				x = row+rowD;
				y = col+colD;
			}

			// repeats
			for(;;)
			{
				// stores the appropriate coordinate
				x += rowD;
				y += colD;

				// breaks if we go off the game board
				if(x<0 || x>= ROWS || y<0 || y>= COLS)
					break;

				// breaks if the space is empty
				if(gameBoard[x][y] == '-')
					break;

				if(gameBoard[x][y] == color)
				{
					// once we hit the next piece that is the same as the one being placed
					// flips all the pieces that need to be flipped
					while(gameBoard[x-=rowD][y-=colD] == opponent)
						gameBoard[x][y] = color;
					break;
				}
			}
		}
	}
}


// counts the current amount of pieces for either color
// Parameters: (gameBoard) - char array representing the game board
// (color) - char representing the color pieces that are being counted
int countPieces(char gameBoard[ROWS][COLS], char color)
{
	// an int to keep track of the piece count
	int totalPieces=0;

	// traverses all the rows and columns
	for(int r=0; r<ROWS; r++)
	{
		for(int c=0; c<COLS; c++)
		{
			// increments the piece count if the space is the appropriate color
			if(gameBoard[r][c] == color)
			{
				totalPieces++;
			}
		}
	}

	// returns the count of pieces
	return totalPieces;
}


// counts the total pieces currently on the board
// Parameters: (gameBoard) - char array representing the game board
int totalPieces(char gameBoard[ROWS][COLS])
{
	// an int to keep track of the total piece count
	int pieces = 0;
	
	// traverses all the rows and columns
	for(int r=0; r<ROWS; r++)
	{
		for(int c=0; c<COLS; c++)
		{
			// increments the count if the space is occupied by a piece
			if((gameBoard[r][c] == 'w') || (gameBoard[r][c] == 'b'))
				pieces++;
		}
	}

	// returns the piece count
	return pieces;
}


// gets a move from the AI
// Parameters: (mover) - the player that is currently moving
// (gameBoard) - char array representing the game board
// (rows + cols) - vectors representing the list of valid rows and columns
// (color) - char representing the color of the AI
// (tracker) - an int to keep track of passes, so as to stop the game after so many passes
void getAIMove(Player mover, char gameBoard[ROWS][COLS], vector<int>& rows, vector<int>& cols, char color, int& tracker)
{
	// an int to store an index
	int index;

	// list the available moves to the AI
	listMovesAI(gameBoard,rows,cols,color);

	// only continues if there are valid moves
	if(rows.size() != 0)
	{
		// chooses a random index between 0 and the size of the array
		index = rand() % rows.size();

		// flips the appropriate discs
		flipDiscs(gameBoard,rows[index],cols[index],color);

		// outpus the message and the game board
		cout << endl << "The computer has made its move." << endl;
		displayBoard(gameBoard);

		// resets the pass tracker
		tracker = 0;
	}

	// if there are no valid moves
	else
	{
		// outputs a message if the AI passes (has no moves)
		cout << "The AI has passed their turn..." << endl;

		// outputs the current game board
		displayBoard(gameBoard);

		// increments the pass tracker
		tracker++;
	}
}


// checks the move for validity
// Parameters: (rows + cols) - vectors of rows and cols that are valid
// (row + col) - the coordinate that needs to be checked
bool checkMove(vector<int>& rows, vector<int>& cols, int& row, int& col)
{
	// traverses the entire vector
	for(unsigned int i=0; i<rows.size(); i++)
	{
		if(rows[i] == row)
		{
			if(cols[i] == col)
			{
				// if the coordinate matches a certain coordinate in the vector
				// returns true
				return true;
			}
		}
	}

	// if there is no match in the vectors, returns false
	return false;
}


// inputs a human move
// Parameters: (gameBoard) - char array representing the game board
// (rows + cols) - vectors of valid rows and columns
// (row + col) - the coordinate passed as a reference
// (color) - char representing the player's color
// (tracker) - a tracker of the passes
void getHumanMove(char gameBoard[ROWS][COLS], vector<int>& rows, vector<int>& cols,
				  int& row, int& col, char color, int& tracker)
{
	// variables for convenience
	char input; bool flag=true; char temp;

	// outputs a list of viable moves
	listMoves(gameBoard,rows,cols,color);

	// while the flag bool is true
	while(flag)
	{
		// inputs if the user wants to pass, or the row number
		cout << "Above is a list of valid moves. " << endl << "Enter 'p' to pass, or enter the row number now : ";
		cin >> input;

		// if the user passes, triggers the flag, increments the tracker, and breaks the loop
		if(input == 'p' || input == 'P')
		{
			cout << "You have chosen to pass...";
			flag = false;
			tracker++;
			break;
		}

		// if the user doesn't pass
		else
		{
			// creates an int from the char row input
			row = input - '0';

			// inputs the column number
			cout << "Enter the column number now : ";
			cin >> temp;

			// creates an int from the char column input
			col = temp - '0';
		}

		// if the move is not valid and the flag has not been triggered
		// outputs a message to the user
		if(checkMove(rows,cols,row,col) == false && flag)
		{
			cout << "Invalid move..." << endl;
		}

		// otherwise, if the move is valid and the flag has not been triggered
		else if(flag)
		{
			// triggers the flag
			flag = false;

			// flips the appropriate discs
			flipDiscs(gameBoard,row,col,color);

			// resets the pass tracker
			tracker = 0;
		}
	}
}


// the main method of the program
void main()
{
	// variables for convenience
	char input; bool inputLoop = true; char board[ROWS][COLS]; bool repeat = true; 
	vector<int> legalRows; vector<int> legalCols; int track = 0; int pieces1 = 0; int pieces2 = 0;
	int r1 = 0; int r2 = 0; int c1 = 0; int c2 = 0;

	// creating the player class for two players
	Player P1 = Player('w',true); Player P2 = Player('b',true);

	// while the repeat bool has not been triggered
	while(repeat)
	{
		// while the inputloop bool has not been triggered
		while(inputLoop)
		{
			// welcome message
			cout << endl << "Welcome to Othello!" << endl << endl;

			// inputs how many AI/Humans are playing
			cout << "For 2 AI enter '1'..." << endl << "For 2 Humans enter '2'..." << endl << "For 1 Human/1 AI enter '3' : ";
			cin >> input;

			// if there are two AI playing, changes the two players appropriately
			// triggers the inputloop bool
			if(input == '1')
			{
				P1.setAI(true); P2.setAI(true);
				inputLoop = false;
			}

			// if there are two humans playing, changes the two players appropriately
			// triggers the inputloop bool
			else if(input == '2')
			{
				P1.setAI(false); P2.setAI(false);
				inputLoop = false;
			}

			// if there is one human and one AI playing, changes the two players appropriately
			// triggers the inputloop bool
			else if(input == '3')
			{
				P1.setAI(false); P2.setAI(true);
				inputLoop = false;
			}

			// if the inputloop bool has not been triggered
			else
			{
				// asks the user for a valid characters
				cout << "Invalid character was inputted... Please enter a valid character..." << endl;
			}
		}
		// resets the inputloop bool
		inputLoop = true;

		// initiates the gameBoard
		initiate(board);

		// if there are two AI playing
		if(input == '1')
		{
			// displays each player's colors and the initial game board
			cout << "Computer Player 1 -> White" << endl << "Computer Player 2 -> Black" << endl;
			displayBoard(board);

			// while the game board is not full and the pass tracker is not past 3 turns
			while(totalPieces(board) < 64 && track < 3)
			{
				// gets the AI move from the Computer Player 1
				getAIMove(P1,board,legalRows,legalCols,P1.getColor(),track);

				// outputs the current score
				cout << "Computer Player 1 : " << countPieces(board, P1.getColor()) << "     " <<
					"Computer Player 2 : " << countPieces(board,P2.getColor()) << endl << endl << "Computer Player 2's Turn... " << endl;

				// resets the vectors containing the valid rows and columns and redisplays the board
				legalRows.clear(); legalCols.clear(); 
				displayBoard(board);

				// gets the AI move from the Computer Player 2
				getAIMove(P2,board,legalRows,legalCols,P2.getColor(),track);

				// outputs the current score
				cout << "Computer Player 1 : " << countPieces(board, P1.getColor()) << "     " <<
					"Computer Player 2 : " << countPieces(board,P2.getColor()) << endl << endl << "Computer Player 1's Turn... " << endl;

				// resets the vectors containing the valid rows and columns and redisplays the board
				legalRows.clear(); legalCols.clear();
				displayBoard(board);
			}

			// after the game, sets variables to store each player's pieces
			pieces1 = countPieces(board,P1.getColor());
			pieces2 = countPieces(board,P2.getColor());

			// announces the winner
			if(pieces1 > pieces2)
			{
				cout << "The game has ended. The winner is Computer Player 1 : " << pieces1 << " to " << pieces2 << ". ";
			}
			else if(pieces2 > pieces1)
			{
				cout << "The game has ended. The winner is Computer Player 2 : " << pieces2 << " to " << pieces1 << ". ";
			}

			// if the pieces are equal, the game is a draw
			else
			{
				cout << "The game has ended in a draw : " << pieces1 << " to " << pieces2 << ". ";
			}
		}

		// if there are two human players
		else if(input == '2')
		{
			// assigns colors to each player and displays the initial game board
			cout << "Player 1 -> White" << endl << "Player 2 -> Black" << endl;
			displayBoard(board);

			// while the board is not full and the pass trackers has not gone past 3 turns
			while(totalPieces(board) < 64 && track < 3)
			{
				// resets the variables and the vectors
				legalRows.clear(); legalCols.clear();
				r1 = 0; r2 = 0; c1 = 0; c2 = 0;

				// gets the move from the human Player 1
				getHumanMove(board,legalRows,legalCols,r1,c1,P1.getColor(),track);

				// outputs the current score
				cout << "Player 1 : " << countPieces(board,P1.getColor()) << "     " << 
					"Player 2 : " << countPieces(board,P2.getColor()) << endl << endl << "Player 2's Turn... " << endl;

				// resets the vectors, variables, and displays the game board
				legalRows.clear(); legalCols.clear();
				displayBoard(board);
				r1 = 0; r2 = 0; c1 = 0; c2 = 0;

				// gets the move from the human Player 2
				getHumanMove(board,legalRows,legalCols,r1,c1,P2.getColor(),track);

				// outputs the current score and displays the current board
				cout << "Player 1 : " << countPieces(board,P1.getColor()) << "     " << 
					"Player 2 : " << countPieces(board,P2.getColor()) << endl << endl << "Player 1's Turn... " << endl;
				displayBoard(board);
			}
			
			// same as before, announces a winner or a draw
			pieces1 = countPieces(board,P1.getColor());
			pieces2 = countPieces(board,P2.getColor());
			if(pieces1 > pieces2)
			{
				cout << "The game has ended. The winner is Player 1 : " << pieces1 << " to " << pieces2 << ". ";
			}
			else if(pieces2 > pieces1)
			{
				cout << "The game has ended. The winner is Player 2 : " << pieces2 << " to " << pieces1 << ". ";
			}
			else
			{
				cout << "The game has ended in a draw : " << pieces1 << " to " << pieces2 << ". ";
			}
		}

		// same as before, except there is one AI and one human
		else if(input == '3')
		{
			cout << "Player 1 -> White" << endl << "Computer -> Black" << endl;
			displayBoard(board);
			while(totalPieces(board) < 64 && track < 3)
			{
				legalRows.clear(); legalCols.clear();
				r1 = 0; r2 = 0; c1 = 0; c2 = 0;
				getHumanMove(board,legalRows,legalCols,r1,c1,P1.getColor(),track);
				cout << endl << "Player 1 : " << countPieces(board,P1.getColor()) << "     " << 
					"Computer : " << countPieces(board,P2.getColor()) << endl << endl << "Computer's Turn... " << endl;
				legalRows.clear(); legalCols.clear();
				displayBoard(board);
				r1 = 0; r2 = 0; c1 = 0; c2 = 0;
				getAIMove(P2,board,legalRows,legalCols,P2.getColor(),track);
				cout << "Player 1 : " << countPieces(board,P1.getColor()) << "     " << 
					"Computer : " << countPieces(board,P2.getColor()) << endl << endl << "Player 1's Turn... " << endl;
				displayBoard(board);
			}
			
			pieces1 = countPieces(board,P1.getColor());
			pieces2 = countPieces(board,P2.getColor());
			if(pieces1 > pieces2)
			{
				cout << "The game has ended. The winner is Player 1 : " << pieces1 << " to " << pieces2 << ". ";
			}
			else if(pieces2 > pieces1)
			{
				cout << "The game has ended. The winner is Computer : " << pieces2 << " to " << pieces1 << ". ";
			}
			else
			{
				cout << "The game has ended in a draw : " << pieces1 << " to " << pieces2 << ". ";
			}
		}
		track = 0;
		// asks the user if they want to play another game
		cout << endl << "Would you like to play another game? (Y/N) : ";
		cin >> input;

		// stops if they say no
		if(input == 'N' || input == 'n')
		{
			cout << "Thanks for playing!" << endl;
			repeat = false;
		}

		// repeats otherwise
	}
	system("pause");

}