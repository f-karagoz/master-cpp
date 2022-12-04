/*
* Title: Deques
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 4 / 12 / 2022
* 
*/

#include <iostream>
#include <deque>
using namespace std;
// random access allowed on deques


int main(void)
{
	deque<int> numbers;
	int temp = 0;

	/* 1 - PUSHING BACK */

	cout << "Pushing Back..." << endl;
	while (temp >= 0)
	{
		cout << "Enter number: ";
		cin >> temp;
		if (temp >= 0)
			numbers.push_back(temp);
	}

	deque<int>::iterator it;
	cout << "{ ";
	for (it = numbers.begin(); it != numbers.end(); it++)
		cout << *it << " ";
	cout << "}";

	/* 2 - PUSHING FRONT */
	
	temp = 0;
	cout << endl;
	cout << "Pushing Front..." << endl;
	while (temp >= 0)
	{
		cout << "Enter number: ";
		cin >> temp;
		if (temp >= 0)
			numbers.push_front(temp);
	}

	cout << "{ ";
	for (it = numbers.begin(); it != numbers.end(); it++)
		cout << *it << " ";
	cout << "}";

	return 0;
}