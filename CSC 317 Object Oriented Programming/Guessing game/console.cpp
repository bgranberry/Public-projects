#include "console.h"

using namespace guessingGame;

string consoleManager::promptFilename(string filename)
{
	cout << "What is the name of the file?" << endl;
	getline(cin, filename);
	cout << "got it" << endl;
	return filename;
}

bool consoleManager::presentQuestion(string question)
{
	char choice;

	cout << question << " answer y/n" << endl;
	while (true)
	{
		cin >> choice;

		if (choice == 'y')
			return true;

		else if (choice == 'n')
			return false;

		else
			cout << "Answer only with 'y' or 'n'" << endl;
	}
}

void consoleManager::verifyAnswer(binary_tree_node <string> *currentPtr)
{
	char choice;
	cout << "I think I've got it! Is the answer a/an " << currentPtr->data() << "?" << endl;

	while (true)
	{

		cin >> choice;

		if (choice == 'y')
		{
			cout << "I knew it!" << endl;
			return;
		}
		else if (choice == 'n')
		{
			cout << "I was sure I was correct..." << endl;
			learn(currentPtr);
			return;
		}
		else
			cout << "Please answer only with 'y' or 'n'" << endl;
	}
}

void consoleManager::learn(binary_tree_node<string> *currentPtr)
{
	string oldAnswer;
	string newQuestion;
	string correctAnswer;

	oldAnswer = currentPtr->data();
	cout << "What was the correct answer?" << endl;
	cin.ignore(256, '\n');
	getline(cin, correctAnswer);
	cout << "Provide a y/n question that would lead to this new answer." << endl;
	getline(cin, newQuestion);
	currentPtr->set_data(newQuestion);
	cout << "Is the correct answer yes, or no? Answer using only 'y' and 'n'" << endl;
	char choice;
	cin >> choice;
	while (true)
	{
		if (choice == 'y')
		{
			delete currentPtr->left();
			delete currentPtr->right();
			currentPtr->set_left(new binary_tree_node<string>(correctAnswer));
			currentPtr->set_right(new binary_tree_node<string>(oldAnswer));
			return;
		}
		else if (choice == 'n')
		{
			delete currentPtr->left();
			delete currentPtr->right();
			currentPtr->set_left(new binary_tree_node<string>(oldAnswer));
			currentPtr->set_right(new binary_tree_node<string>(correctAnswer));
			return;
		}
		else
		{
			cout << "Please answer using only 'y' and 'n'" << endl;
		}
	}
}

bool consoleManager::promptReplay()
{
	char choice;

	cout << "Would you like to play again? y/n" << endl;

	while (true)
	{
		cin >> choice;

		if (choice == 'y')
		{
			cout << "Starting over..." << endl;
			return true;
		}
		else if (choice == 'n')
		{
			cout << "Have a good day!" << endl;
			return false;
		}
		else
			cout << "Please answer only with 'y' or 'n'" << endl;
	}

}