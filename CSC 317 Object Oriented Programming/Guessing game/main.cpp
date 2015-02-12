/*This game simulates the popular game “20 Questions”.A computer asks the player a 
series of questions to narrow down the possible known answers, and then asks the 
player if it was correct when it has exhausted its questions.If not correct, it 
can “learn” from the player by having him / her provide it with a question to distinguish 
the new answer from the incorrect one.This game also has a hint mode 
implemented using a tag system.It asks the player to 
pick from a list of tags that are the combination of all the tags on the 
possible answers the computer knows.*/

#include "game.h"
using namespace guessingGame;

int main()
{
	string choice;
	gameManager game = gameManager();

	cout << "Would you like to play the game with hints? y/n" << endl;
	while (true)
	{
		cin >> choice;

		if (choice == "y")
		{
			game.play_hints();
			break;
		}
		else if (choice == "n")
		{
			game.play();
			break;
		}
		else
			cout << "Answer only with 'y' or 'n'" << endl;

	}
	return 0;
}