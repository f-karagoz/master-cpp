/*
* Title: Sets
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*/

#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

// associative container
// addresses elements by content rather than address
// duplicates are ignored in sets

int main(void)
{
	set<int> this_set;
	int temp = 0;

	/* 1 - Insert elements */

	cout << "Inserting..." << endl;
	while (temp >= 0)
	{
		cout << "Enter number: ";
		cin >> temp;
		if (temp >= 0)
			this_set.insert(temp);
	}

	/* Print out */
	cout << "{ ";
	for (auto it = this_set.begin(); it != this_set.end(); ++it)
		cout << *it << " ";
	cout << "}" << endl;

	/* 2 - Remove by element */

	temp = 0;
	cout << "Removing..." << endl;
	while (temp >= 0)
	{
		cout << "Enter number: ";
		cin >> temp;
		if (temp >= 0)
			this_set.erase(temp);
	}

	/* Print out */
	cout << "{ ";
	for (auto it = this_set.begin(); it != this_set.end(); ++it)
		cout << *it << " ";
	cout << "}" << endl;

	return 0;
}