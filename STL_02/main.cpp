/*
* Title: STL Vectors
* Author: Furkan Karagoz
* Instuctor: Eduardo Corpeno
* Date: 3 / 12 / 2022
*/

#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& my_vector)
{
	cout << "Vector content { ";

	for (const int& num : my_vector)
		cout << num << " ";

	cout << "}\n\n";
}


int main(void)
{
	vector<int> numbers;
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
			numbers.insert(numbers.begin(), value);
	}
	print(numbers);

	/* 3 - INSERT BY INDEX  */

	int index = 0;

	cout << "Inserting by index...\n";
	while (index >= 0)
	{
		cout << "Enter index: ";
		cin >> index;
		if (index >= 0)
		{
			cout << "Enter value: ";
			cin >> value;
			numbers.insert(numbers.begin() + index, value);
		}
			
	}
	print(numbers);

	/* 4 - MODIFY EXISTING ELEMENTS  */

	index = 0;

	cout << "Modifying existing elements...\n";
	while (index >= 0)
	{
		cout << "Enter index: ";
		cin >> index;
		if (index >= 0)
		{
			cout << "Enter value: ";
			cin >> value;
			numbers[index] = value;
		}

	}
	print(numbers);

	return 0;
}