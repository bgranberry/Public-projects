#include "tictactoe.h"

using namespace std;


int main(){

	char playerChoice;
	int move;
	char anykey;

	

	cout << "X/O?" << endl;
	cin >> playerChoice;

	ticTacToe bot(playerChoice); 
	bot.initializeBoard();

	if (playerChoice == 'O')
		bot.makeFirstMove();

	bot.printBoard();

	while (true)
	{

		//usr input cin and stuff
		cout << "where to place mark?" << endl;
		cin >> move;
		bot.userMakeMove(move);
		bot.printBoard();

		if (bot.gameWon() || bot.isFull())
		{
			break;
		}
		else
			bot.makeMove();

		if (bot.gameWon() || bot.isFull())
			break;

		bot.printBoard();

		cout << "press any key to continue" << endl;
		cin >> anykey;
		
	}

	bot.printBoard();
	bot.gameOver();
	
	cout << "any key to exit" << endl;

	cin >> anykey;



	return 0;
}