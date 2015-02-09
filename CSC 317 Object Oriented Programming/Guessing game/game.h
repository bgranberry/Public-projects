#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <cassert>
#include <string>
#include "bintree.h"
#include "console.h"

using namespace main_savitch_10;
using namespace std;

namespace guessingGame
{
	class gameManager
	{
	public:
		gameManager();
		void play();// const;
		void read();
		void write();
		void write()const;
	private:
		binary_tree_node<string> *rootPtr;
		consoleManager *console;
		string filename;
	};

}

#endif