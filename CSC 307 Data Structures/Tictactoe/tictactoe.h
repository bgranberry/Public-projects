#ifndef TICTACTOE_PLAYER_CLASS
#define TICTACTOE_PLAYER_CLASS
#include <iostream>
#include <cassert>
#include <stdlib.h>


using namespace std;



class ticTacToe
{
public:
	ticTacToe(char playerChoice);

	void initializeBoard();
	void makeFirstMove();
	void makeMove();
	void userMakeMove(int move);
	int bestMove();
	bool isOccupied(int target);
	bool gameWon();
	bool isFull();
	void gameOver();
	void printBoard();


private:
	char myMark, p2Mark;
	char board[9];
	int lastMove;
	char occupiedSpace;
	char winner = 'C';


};


void ticTacToe::initializeBoard()
{
	for (int i = 0; i <= 8; i++)
		board[i] = '-';

}


ticTacToe::ticTacToe(char playerChoice)
{

	assert(playerChoice == 'X' || playerChoice == 'O');

	if(playerChoice == 'X')
	{
		myMark = 'O';
		p2Mark = 'X';
	}
	else 
	{
		myMark = 'X';
		p2Mark = 'O';
	}

}


void  ticTacToe::makeFirstMove()
{
	int target;
//pick random spot in index, excluding edges (only 1,3,5,7,9)

	target = rand() % 9;

	board[target] = myMark;

}

void ticTacToe::makeMove()
{
	int target = bestMove();

	if (!isOccupied(target))
		board[target] = myMark;
	
}

void ticTacToe::userMakeMove(int move)
{
	int target = move;
	
	if (!isOccupied(target))
		board[target] = p2Mark;
	else
	{
		cout << "non valid space. choose again" << endl;
		cin >> move;
		userMakeMove(move);
	}
}

int ticTacToe::bestMove()
{
	//win first, block second 

	int n = 0;

	//horizontal checking for block/win
	while (n <= 6)
	{
		if (board[n] != '-' && board[n] == board[n + 1] && board[n + 2] == '-') return 2;
		if (board[n] != '-' && board[n] == board[n + 2] && board[n + 1] == '-') return 1;
		if (board[n + 1] != '-' && board[n + 1] == board[n + 2] && board[n] == '-') return 0;

		n += 3;
	}

	//reset n
	n = 0;

	//vertical check for block/win
	while (n <= 2)
	{
		if (board[n] != '-' && board[n] == board[n + 3] && board[n + 6] == '-') return 6;
		if (board[n] != '-' && board[n] == board[n + 6] && board[n + 3] == '-') return 3;
		if (board[n + 3] != '-' && board[n + 3] == board[n + 6] && board[n] == '-') return 0;

		n++;

	}

	//right diagonal check
	if (board[0] != '-' && board[0] == board[4] && board[8] == '-') return 8;
	if (board[0] != '-' && board[0] == board[8] && board[4] == '-') return 4;
	if (board[4] != '-' && board[4] == board[8] && board[0] == '-') return 0;

	//left diagonal check
	if (board[2] != '-' && board[2] == board[4] && board[6] == '-') return 6;
	if (board[2] != '-' && board[2] == board[6] && board[4] == '-') return 4;
	if (board[4] != '-' && board[4] == board[6] && board[2] == '-') return 2;

	// if there is no win or block to make continue by picking highest value spots first
	//center is most valuable
	if (board[4] == '-') return 4;
	
	n = 0;

	//corners next
	while (n <= 8)
	{
		if (n%2 == 0)
			if (board[n] == '-') return n;
		n++;
	}
	//edges are lowest value
	while (n <= 8)
	{
		if (n % 2 == 1)
			if (board[n] == '-') return n;
		n++;
	}

}

bool ticTacToe::isOccupied(int target)
{
	if (board[target] == 'X' || board[target] == 'O')
	{
		occupiedSpace = board[target];
		return true;
	}
	else 
		return false;


}

bool ticTacToe::gameWon()
{
	//biz fixed ithink
	int n;

		//vert check
		n = 0;
		for (n; n <= 2; n++)
		{
			if (board[n] == 'X' && board[n] == board[n + 3] && board[n] == board[n + 6])
			{
				winner = 'X';
					return true;
			}

			if (board[n] == 'O' && board[n] == board[n + 3] && board[n] == board[n + 6])
			{
				winner = 'O';
				return true;

			}
		}

		//horizontal check
		n = 0;
		for (n; n <= 6; n+=3)
		{

			if (board[n] == 'X' && board[n] == board[n + 1] && board[n] == board[n + 2])
			{
				winner = 'X';
				return true;
			}

			if (board[n] == 'O' && board[n] == board[n + 1] && board[n] == board[n + 2])
			{
				winner = 'O';
				return true;
			}


		}
	
		//left right diagonal check
		n = 0;
		if (board[n] == 'X' && board[n] == board[n + 4] && board[n] == board[n + 8])
		{
			winner = 'X';
			return true;
		}

		if (board[n] == 'O' && board[n] == board[n + 4] && board[n] == board[n + 8])
		{
			winner = 'O';
			return true;
		}


		//right left diagonal check

		if (board[n] == 'X' && board[n] == board[n + 2] && board[n] == board[n + 4])
		{
			winner = 'X';
			return true;
		}

		if (board[n] == 'O' && board[n] == board[n + 2] && board[n] == board[n + 4])
		{
			winner = 'O';
			return true;
		}

		return false;
	
}

bool ticTacToe::isFull()
{
	for (int i = 0; i <= 8; i++)
	{
		if (board[i] != 'X' && board[i] != 'O')
			return false;
	}

	return true;
}

void ticTacToe::gameOver()
{
	if (winner == myMark)
		cout << "Winner is computer. Better luck next time" << endl;

	if (winner == p2Mark)
		cout << "Winner is human." << endl;
	
	if (winner == 'C')
		cout << "Draw. Try again?" << endl;

}


void ticTacToe::printBoard()
{
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << "---|---|---" << endl;
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "---|---|---" << endl;
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << "---|---|---" << endl << endl;
}



#endif