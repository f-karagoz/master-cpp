/*
* Title: Challenge: Hotel Rooms
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*
* Coordinates are used in GPS
* Pair of integers
* 34 24' N, 90 W -> 34, 270
* We expect to have as many as pins needed, all typed in
* There are infinite coordinates
* Two dimensional inxed coordinates is not an option
* Indexes are discrete, coordinates are continuous
* Out model has 360 x 360 coordinates
*
* Keep track of guests in a hotel
* The hotel has 20 floors with 15 rooms each
* Rooms are numbered as [floor #][roomn #] 114 or 1408
* No duplicates allowed
* Guest objects may take consdereable storage not just name
* Room numbers outside the format does not exist: 2, 100, 1816, 2204
* 
* Test code:
* Enter series of room numbers with names
* Print them out
* Enter duplicate key for an existing entry with differnt name, should not modify the container
* Delete the existing entry
* Print it all
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(void)
{
	map<pair<int, int>, string> rooms;
	int temp = 0;
	string str;
	pair<pair<int, int>, string> p;
	pair<int, int> roomNumber;

	/* 1 - Insert elements */

	cout << "Inserting..." << endl;
	while (temp >= 0)
	{
		cout << "Enter floor number: ";
		getline(cin, str);
		temp = stoi(str);
		if (temp > 0)
		{
			if (temp <= 20)
			{
				roomNumber.first = temp;

				cout << "Enter floor room number: ";
				getline(cin, str);
				temp = stoi(str);

				roomNumber.second = temp;

				if (temp >= 1 && temp <= 15)
				{
					p.first = roomNumber;

					cout << "Enter resident name: ";
					getline(cin, str);
					p.second = str;

					rooms.insert(p);
				}
				else
					continue;
			}
			else
				continue;
		}
	}

	/* Print elements */
	cout << "\n{\n";
	for (auto it = rooms.begin(); it != rooms.end(); ++it)
		cout << it->first.first << it->first.second << "->" << it->second << endl;
	cout << "}\n\n";

	/* 2 - Delete elements */

	temp = 0;
	cout << "Deleting..." << endl;
	while (temp >= 0)
	{
		cout << "Enter floor number: ";
		getline(cin, str);
		temp = stoi(str);
		if (temp > 0)
		{
			if (temp <= 20)
			{
				roomNumber.first = temp;

				cout << "Enter floor room number: ";
				getline(cin, str);
				temp = stoi(str);

				roomNumber.second = temp;

				if (temp >= 1 && temp <= 15)
				{
					cout << "Log for room " << rooms.find(roomNumber)->first.first
						<< rooms.find(roomNumber)->first.second << " deleted." << endl;

					rooms.erase(roomNumber);
				}
				else
					continue;
			}
			else
				continue;
		}
	}

	/* Print elements */
	cout << "\n{\n";
	for (auto it = rooms.begin(); it != rooms.end(); ++it)
		cout << it->first.first << it->first.second << "->" << it->second << endl;
	cout << "}\n\n";

	return 0;
}