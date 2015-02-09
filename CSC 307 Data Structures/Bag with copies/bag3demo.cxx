// FILE: bag3demo.cxx
// Demonstration program for the 3rd version of the bag (bag3.h and bag3.cxx).
// This is a the same as the demonstration program for bag1,
// except that we no longer need to check whether the bag reaches its
// capacity.

#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "bag3.h"       // With Item defined as an int
using namespace std;
using namespace main_savitch_5;

// PROTOTYPES for functions used by this demonstration program:
void get_ages(bag& ages);
// Postcondition: The user has been prompted to type in the ages of family
// members. These ages have been read and placed in the ages bag, stopping
// when the user types a negative number.

void check_ages(bag& ages);
// Postcondition: The user has been prompted to type in the ages of family
// members once again. Each age is removed from the ages bag when it is typed,
// stopping when the bag is empty.


int main( )
{
    bag ages;

    get_ages(ages);
    check_ages(ages);
    cout << "May your family live long and prosper." << endl;
    return EXIT_SUCCESS;  
}


void get_ages(bag& ages)
{
    int user_input; // An age from the user's family

    cout << "Type the ages in your family. ";
    cout << "Type a negative number when you are done:" << endl;
    cin >> user_input;
    while (user_input >= 0)
    {
        ages.insert(user_input);
        cin >> user_input;
    }
}

void check_ages(bag& ages)
{
    int user_input; // An age from the user's family

	cout << "Would you like to (1)delete each entry individually, or (2)delete all duplicate instances of each entry? choose 1 or 2" << endl;
	cin >> user_input;

	if (user_input == 1)
	{
		cout << "Type those ages again. Press return after each age:" << endl;
		while (ages.size() > 0)
		{
			cin >> user_input;
			if (ages.erase_one(user_input))
				cout << "Yes, I've got that age and have removed it." << endl;
			else
				cout << "No, that age does not occur!" << endl;
		}
	}
	else if (user_input == 2)
	{
		cout << "Type those ages again. Press return after each age:" << endl;
		while (ages.size() > 0)
		{
			cin >> user_input;
			if (ages.erase(user_input))
				cout << "Yes, I've got that age and have removed it." << endl;
			else
				cout << "No, that age does not occur!" << endl;
		}
	}
}


//new insert
/*
if (head_ptr == NULL)
	{
		head_prt = new node (pair, head_ptr)
	}
else (if list search (entry))
		increment count on existing node
else create new node 
	first compare each existing nodes data to the new data, and place in list accordingly 

*/