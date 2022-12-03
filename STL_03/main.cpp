/*
* Title: STL Lists
* Author: Furkan Karagoz
* Instuctor: Eduardo Corpeno
* Date: 3 / 12 / 2022
*/

#include <iostream>
#include <list>
using namespace std;

void print(const list<int>& my_list)
{
	cout << "List content { ";

	for (const int& num : my_list)
		cout << num << " ";

	cout << "}\n\n";
}


int main(void)
{
	list<int> numbers;
	int value = 0;

	/* 1 - PUSHING BACK  */

	cout << "Pushing back...\n";
	while (value >= 0)
	{
		cout << "Enter number: ";
		cin >> value;
		if (value >= 0)
			numbers.push_back(value);
	}
	print(numbers);

	/* 2 - PUSHING FRONT  */

	value = 0;
	cout << "Pushing front...\n";
	while (value >= 0)
	{
		cout << "Enter number: ";
		cin >> value;
		if (value >= 0)
			numbers.push_front(value);
	}
	print(numbers);

	// No random access allowed in lists

	return 0;
}