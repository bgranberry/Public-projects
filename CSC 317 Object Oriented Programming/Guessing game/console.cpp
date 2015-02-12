#include "console.h"

using namespace guessingGame;
void addNewTags(binary_tree_node<string> *currentPtr, vector<string> tag_key)
{
	int choice = 0;

	cout << "Please add all tags that apply to this new answer(type only the index number). Type '-1' when done." << endl;

	for (unsigned i = 0; i < tag_key.size(); i++)
	{
		cout << i << '-' << tag_key[i] << endl;
	}

	while (choice != -1)
	{
		cin >> choice;
		if (static_cast<unsigned>(choice) >= 0 && static_cast<unsigned>(choice) < tag_key.size())
		{
			currentPtr->tags().push_back(choice);
			cout << "Tag added" << endl;
		}
		else
			cout << "Invalid index" << endl;
	}
	cout << "Thank you. This new entry has been updated." << endl;
}


string consoleManager::promptFilename(string &filename)
{
	cout << "What is the name of the file?" << endl;
	cin >> filename;
	cout << "got it" << endl;
	return filename;
}

bool consoleManager::presentQuestion(string question)
{
	string choice;

	cout << question << " answer y/n" << endl;
	while (true)
	{
		cin >> choice;

		if (choice == "y")
			return true;

		else if (choice == "n")
			return false;

		else
			cout << "Answer only with 'y' or 'n'" << endl;
	}
}

void consoleManager::verifyAnswer(binary_tree_node <string> *currentPtr, vector<string> tag_key)
{
	string choice;
	cout << "I think I've got it! Is the answer a/an " << currentPtr->data() << "?" << endl;

	while (true)
	{

		cin >> choice;

		if (choice == "y")
		{
			cout << "I knew it!" << endl;
			return;
		}
		else if (choice == "n")
		{
			cout << "I was sure I was correct..." << endl;
			learn(currentPtr, tag_key);
			return;
		}
		else
			cout << "Please answer only with 'y' or 'n'" << endl;
	}
}

void consoleManager::learn(binary_tree_node<string> *currentPtr, vector<string> tag_key)
{
	binary_tree_node<string> *oldAnswer = new binary_tree_node<string>(currentPtr->data());
	oldAnswer->tags() = currentPtr->tags();

	string newQuestion;
	string correctAnswer;

	cout << "What was the correct answer?" << endl;
	cin.ignore(256, '\n');
	getline(cin, correctAnswer);
	cout << "Provide a y/n question that would lead to this new answer." << endl;
	getline(cin, newQuestion);
	currentPtr->set_data(newQuestion);
	cout << "Is the correct answer yes or no? Answer using only 'y' and 'n'" << endl;

	string choice;
	cin >> choice;
	while (true)
	{
		if (choice == "y")
		{
			delete currentPtr->left();
			delete currentPtr->right();
			currentPtr->set_left(new binary_tree_node<string>(correctAnswer));
			currentPtr->set_right(oldAnswer);
			addNewTags(currentPtr->left(), tag_key);
			return;
		}
		else if (choice == "n")
		{
			delete currentPtr->left();
			delete currentPtr->right();
			currentPtr->set_left(oldAnswer);
			currentPtr->set_right(new binary_tree_node<string>(correctAnswer));
			addNewTags(currentPtr->right(), tag_key);
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
	string choice;

	cout << "Would you like to play again? y/n" << endl;

	while (true)
	{
		cin >> choice;

		if (choice == "y")
		{
			cout << "Starting over..." << endl;
			return true;
		}
		else if (choice == "n")
		{
			cout << "Have a good day!" << endl;
			return false;
		}
		else
			cout << "Please answer only with 'y' or 'n'" << endl;
	}

}