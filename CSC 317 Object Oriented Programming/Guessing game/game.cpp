#include "game.h"

using namespace guessingGame;

//Prototypes for non-member functions
void preorderRead(ifstream &inFile, string line, binary_tree_node<string> *currentPtr);
void preorderPrint(ofstream &outFile, binary_tree_node<string> *currentPtr);

gameManager::gameManager()
{
	console = new consoleManager();
	read();
}

void gameManager::play()//const 
{
	binary_tree_node<string> *currentPtr = rootPtr;

	cout << "Lets play a game! Think of an item within a domain, and I'll try to guess it!" << endl;

	//set up loop, while not at answer(leaf node)
	while (currentPtr->left() != NULL && currentPtr->right() != NULL)
	{
		if (console->presentQuestion(currentPtr->data()))
			currentPtr = currentPtr->left();
		else
			currentPtr = currentPtr->right();
	}

	console->verifyAnswer(currentPtr);

	if (console->promptReplay())
		play();
	else
		write();

}



void gameManager::read()
{
	string line;
	ifstream inFile;
	binary_tree_node<string> *currentPtr;


	inFile.open(console->promptFilename(filename));
	//assert that the file is opened; otherwise crash
	assert(inFile.is_open());

	getline(inFile, line);
	rootPtr = new binary_tree_node<string>(line);
	currentPtr = rootPtr;

	preorderRead(inFile, line, currentPtr);


}

void gameManager::write()
{
	ofstream outFile;
	binary_tree_node<string> *currentPtr = rootPtr;
	outFile.open("out.txt");

	preorderPrint(outFile, currentPtr);
}

void gameManager::write()const
{
	ofstream outFile;
	binary_tree_node<string> *currentPtr = rootPtr;
	outFile.open("out.txt");

	preorderPrint(outFile, currentPtr);

}


//Non-member functions
void preorderRead(ifstream &inFile, string line, binary_tree_node<string> *currentPtr)
{
	if (!inFile.eof())
	{
		if (inFile.peek() != '$')
		{
			getline(inFile, line);
			currentPtr->left() = new binary_tree_node<string>(line);
			preorderRead(inFile, line, currentPtr->left());

			if (inFile.peek() != '$')
			{
				getline(inFile, line);
				currentPtr->right() = new binary_tree_node<string>(line);
				preorderRead(inFile, line, currentPtr->right());
				return;
			}
			else //case where one leaf node must be inserted to the right when not at deepest level
			{
				inFile.ignore(256, '\n');
				getline(inFile, line);
				currentPtr->right() = new binary_tree_node<string>(line);
				return;
			}
		}
		else//program has encountered leaf node(s)
		{
			//left node will be leaf
			inFile.ignore(256, '\n'); //discards '$' from stream
			getline(inFile, line);
			currentPtr->left() = new binary_tree_node<string>(line);

			//right node will be leaf
			if (inFile.peek() == '$')
			{
				inFile.ignore(256, '\n'); //discards '$' from stream
				getline(inFile, line);
				currentPtr->right() = new binary_tree_node<string>(line);
			}
			else //right leaf is not leaf, and must continue reading down this path
			{
				getline(inFile, line);
				currentPtr->right() = new binary_tree_node<string>(line);
				preorderRead(inFile, line, currentPtr->right());
			}
			return;
		}

	}

}
void preorderPrint(ofstream &outFile, binary_tree_node<string> *currentPtr)
{
	if (currentPtr != NULL)
	{
		outFile << currentPtr->data() << endl;

		if (currentPtr->left() != NULL && currentPtr->left()->left() == NULL)
			outFile << '$' << endl;

		preorderPrint(outFile, currentPtr->left());

		if (currentPtr->right() != NULL && currentPtr->right()->right() == NULL)
			outFile << '$' << endl;

		preorderPrint(outFile, currentPtr->right());

	}

}