/*
* Title: Example Lanmark Pins
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
* 
* Coordimnates are used in GPS
* Pair of integers
* 34 24' N, 90 W -> 34, 270
* We expect to have as many as pins needed, all typed in
* There are infinite coordinates
* Two dimensional inxed coordinates is not an option
* Indexes are discrete, coordinates are continuous
* Out model has 360 x 360 coordinates
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void)
{
	map<pair<int,int>, string> pins;
	int temp = 0;
	string str;
	pair<pair<int,int>, string> p;
	pair<int, int> landmark;

	/* 1 - Insert elements */

	cout << "Inserting..." << endl;
	while (temp >= 0)
	{
		cout << "Enter latitude: ";
		getline(cin, str);
		temp = stoi(str);
		if (temp >= 0)
		{
			landmark.first = temp;

			cout << "Enter longtitude: ";
			getline(cin, str);
			temp = stoi(str);

			landmark.second = temp;
			p.first = landmark;

			cout << "Enter name: ";
			getline(cin, str);
			p.second = str;

			pins.insert(p);
		}
	}

	/* Print elements */
	cout << "{ ";
	for (auto it = pins.begin(); it != pins.end(); ++it)
		cout << it->first.first << "," << it->first.second << "->" << it->second << " ";
	cout << "}" << endl;

	return 0;
}