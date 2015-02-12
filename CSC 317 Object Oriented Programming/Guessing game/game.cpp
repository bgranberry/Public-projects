#include "game.h"

using namespace guessingGame;

//Prototypes for non-member functions
void preorderRead(ifstream &inFile, string line, binary_tree_node<string> *currentPtr);
void preorderPrint(ofstream &outFile, binary_tree_node<string> *currentPtr);
bool search_tags(vector<int> currentPtr, int hint);

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

	console->verifyAnswer(currentPtr, tag_key);

	if (console->promptReplay())
		play();
	else
		write();


}

void gameManager::play_hints()
{
	binary_tree_node<string> *currentPtr = rootPtr;
	int hint = 0;

	currentPtr->set_tags(currentPtr); //sets up tree to use the tag system

	cout << "Lets play a game! Think of an item within a domain, and I'll try to guess it!" << endl;
	cout << "But first, can you give me a hint? Please pick from this list of traits(Type only the index)." << endl;


	//Menu to select hint choice
	for (unsigned i = 0; i < tag_key.size(); i++)
	{
		cout << i << '-' << tag_key[i] << endl;
	}

	while (cin)
	{
		cin >> hint;
		if (static_cast<unsigned>(hint) >= 0 && static_cast<unsigned>(hint) < tag_key.size())
			break;
		else
			cout << "Invalid index" << endl;
	}

	//begin looking for answer
		while (!currentPtr->is_leaf())
		{
			//possible answers exist in both subtrees
			if (search_tags(currentPtr->Ltags(), hint) && search_tags(currentPtr->Rtags(), hint))
			{
				if (console->presentQuestion(currentPtr->data()))
					currentPtr = currentPtr->left();
				else
					currentPtr = currentPtr->right();
			}
			//answer(s) is in left subtree
			else if (search_tags(currentPtr->Ltags(), hint)  && !search_tags(currentPtr->Rtags(), hint))
			{
				currentPtr = currentPtr->left();
			}
			//answer(s) is in right subtree
			else if (!search_tags(currentPtr->Ltags(), hint) && search_tags(currentPtr->Rtags(), hint))
			{
				currentPtr = currentPtr->right();
			}
			else
			{
				cout << "What happened?" << endl;
			}
		}
	//leaf is reached, check for win
	console->verifyAnswer(currentPtr, tag_key);

	if (console->promptReplay())
		play_hints();
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

	getline(inFile, line);//ignores "Tags:"
	while (inFile.peek() != '#')
	{
		getline(inFile, line, '-');
		getline(inFile, line);
		tag_key.push_back(line);
	}

	getline(inFile, line);//ignores"###"

	getline(inFile, line);
	rootPtr = new binary_tree_node<string>(line);
	currentPtr = rootPtr;

	preorderRead(inFile, line, currentPtr);
}

void gameManager::write()
{
	ofstream outFile;
	binary_tree_node<string> *currentPtr = rootPtr;

	console->promptFilename(filename);
	outFile.open(filename);

	outFile << "Tags:" << endl;
	for (unsigned int i = 0; i < tag_key.size(); i++)
	{
		outFile << i << '-' << tag_key[i] << endl;
	}
	outFile << "###" << endl;

	preorderPrint(outFile, currentPtr);
}


//Non-member functions
void preorderRead(ifstream &inFile, string line, binary_tree_node<string> *currentPtr)
{
	int fileTag;
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
				getline(inFile, line, '-');
				currentPtr->right() = new binary_tree_node<string>(line);
				//inFile >> fileTag;
				while (inFile.peek() != '\n')
				{
					inFile >> fileTag;
					if (inFile.eof())
						break;
					currentPtr->right()->tags().push_back(fileTag);
				}
				inFile.ignore(1);//ignores \n
				return;
			}
		}
		else//program has encountered leaf node(s)
		{
			//left node will be leaf
			inFile.ignore(256, '\n'); //discards '$' from stream
			getline(inFile, line, '-');
			currentPtr->left() = new binary_tree_node<string>(line);

			//gets tags associated with item from the same line
			while (inFile.peek() != '\n')
			{
				inFile >> fileTag;
				currentPtr->left()->tags().push_back(fileTag);
			}
			inFile.ignore(1); // ignores \n
			
			//right node will be leaf
			if (inFile.peek() == '$')
			{
				inFile.ignore(256, '\n'); //discards '$' from stream
				getline(inFile, line, '-');
				currentPtr->right() = new binary_tree_node<string>(line);

				//gets tags associated with item from the same line
				while (inFile.peek() != '\n')
				{
					inFile >> fileTag;
					currentPtr->right()->tags().push_back(fileTag);
				}
				inFile.ignore(1);
			}
			else //right node is not leaf, and must continue reading down this path
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
		outFile << currentPtr->data();
		if (currentPtr->is_leaf())
		{
			outFile << '-';
			for (unsigned i = 0; i < currentPtr->tags().size(); i++)
			{
				outFile << currentPtr->tags()[i];
				if (i < currentPtr->tags().size() - 1)
					outFile << ' ';
			}
		}
		outFile << endl;


		if (currentPtr->left() != NULL && currentPtr->left()->left() == NULL)
		{
			outFile << '$' << endl;
		}
		preorderPrint(outFile, currentPtr->left());

		if (currentPtr->right() != NULL && currentPtr->right()->right() == NULL)
			outFile << '$' << endl;

		preorderPrint(outFile, currentPtr->right());

	}
}
bool search_tags(vector<int> currentPtr, int hint)
{

	for (unsigned i = 0; i < currentPtr.size(); i++)
	{
		if (currentPtr[i] == hint)
			return true;
	}
	return false;
}
