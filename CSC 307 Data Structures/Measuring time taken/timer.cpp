#include <iostream>
#include <chrono>
#include <cstdlib>
#include "bag6.h"

using namespace std;

int main()
{
	int n;
	cout << "Please specify the number of items to generate in the bag." << endl;
	cin >> n;
	main_savitch_10::bag<int> bag;
	srand(time(NULL));


	std::clock_t start;
	double duration;

	start = clock();

	for (int i = n; i >= 1; i--)
	{
		bag.insert(rand());
	}

	for (int j = 1; j < n; j++)
	{
		bag.count(j);
	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time it took to fill the bag and count it: " << duration << endl;

	return 0;
	
}