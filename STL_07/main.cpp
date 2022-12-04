/*
* Title: Stack
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*
*/

#include <iostream>
#include <stack>
using namespace std;
// insertion only allowed on one end

int main(void)
{
	stack<int> numbers;
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
		cout << numbers.top() << " ";
		numbers.pop();
	}
	cout << "}";


	return 0;
}