/*
* Title: Queue
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*
*/

#include <iostream>
#include <queue>
using namespace std;

int main(void)
{
	queue<int> numbers;
	int temp = 0;

	cout << "Pushing..." << endl;
	while (temp >= 0)
	{
		cout << "Enter numbers: ";
		cin >> temp;
		if (temp >= 0)
			numbers.push(temp);
	}

	cout << "{ ";

	while (numbers.size() != 0)
	{
		cout << numbers.front() << " ";
		numbers.pop();
	}
	cout << "}";

	// Stack is LIFO
	// Queue is FIFO

	return 0;
}