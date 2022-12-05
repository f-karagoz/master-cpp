/*
* Title: Maps ans variants
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022 
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main(void)
{
	// <key,content>
	//map<int, string> this_map;
	multimap<int, string> this_map;
	int temp = 0;
	string str;
	pair<int, string> p;

	/* 1 - Insert elements */

	cout << "Inserting..." << endl;
	while (temp >= 0)
	{
		cout << "Enter key: ";
		getline(cin, str);
		temp = stoi(str);
		if (temp >= 0)
		{
			p.first = temp;
			cout << "Enter name: ";
			getline(cin, str);
			p.second = str;
			this_map.insert(p);
		}
	}

	/* Print elements */
	cout << "{ ";
	for (auto it = this_map.begin(); it != this_map.end(); ++it)
		cout << it->first << "->" << it->second << " ";
	cout << "}" << endl;


	/* 2 - Remove elements */

	temp = 0;
	cout << "Removing..." << endl;
	while (temp >= 0)
	{
		cout << "Enter key: ";
		getline(cin, str);
		temp = stoi(str);
		if (temp >= 0)
		{
			this_map.erase(temp);
		}
	}

	/* Print elements */
	cout << "{ ";
	for (auto it = this_map.begin(); it != this_map.end(); ++it)
		cout << it->first << "->" << it->second << " ";
	cout << "}" << endl;

	return 0;
}