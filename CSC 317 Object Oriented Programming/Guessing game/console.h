#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;
namespace guessingGame
{

	class consoleManager
	{
	public:
		string promptFilename(string &filename);
		bool presentQuestion(string question);
		void verifyAnswer(binary_tree_node <string> *currentPtr, vector<string> tag_key);
		void learn(binary_tree_node<string> *currentPtr, vector<string> tag_key);
		bool promptReplay();
	};


}
#endif