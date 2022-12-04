/**
* Title: Birthday Party : Challenge
* Author: Furkan Karagoz
* Instructor: Eduardo Corpena
* Date: 4 / 12 / 2022
* Tasks			Print guest's data by index
*				Remove a guest by index
*				Calculate the average age in the group
* 
* Tets cases:	Enter series of objects into text file
*				Print all guests
*				Print one guest information by index, eg. 3
*				Remove the same guest by index
*				Print all guests again
*				Get average group age
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

//#define USE_VECTOR
#define USE_LIST

class guest
{
public:
	guest() {}
	~guest() {}

	void set_gender(string gender_)
	{
		char i = gender_.c_str()[0];
		if (i == 'b' || i == 'B' || i == 'm' || i == 'M')
			gender = "Boy";
		else
			gender = "Girl";
	}

	string name;
	string gender;
	int age;
};

#ifdef USE_VECTOR
typedef vector<guest> my_container;
#elif defined USE_LIST
typedef list<guest> my_container;
#endif

void read_file(my_container* my_guests)
{
	string in_str;
	ifstream in_file("my_guests.txt");	// constructor of the ifstream allows us to put the file name that we want to input
	if (in_file.is_open())
	{
		guest temp;
		while (getline(in_file, in_str))
		{
			temp.name = in_str;
			getline(in_file, in_str);
			temp.set_gender(in_str);
			getline(in_file, in_str);
			temp.age = stoi(in_str);
			my_guests->push_back(temp);
		}
		in_file.close();
	}
	else
		cout << "Unable to open file!\n\n";
}

void print_guests(my_container* my_guests)
{
	auto it = my_guests->begin();
	cout << "-- Container Content Start --\n";
	cout << "-----------------------------\n";
	// < operator is random acces which is not supported in lists
	//while ( it < my_guests->end() )
	while (it != my_guests->end())
	{
		cout << "Name:\t" << it->name << endl;
		cout << "Gender:\t" << it->gender << endl;
		cout << "Age:\t" << it->age << endl;
		it++;
		cout << "-----------------------------\n";
	}
	cout << "--  Container Content End  --\n\n";
}

void print_guests(my_container* my_guests, int index)
{
	auto it = my_guests->begin();
	cout << "--   Guest with index: " << index << "   --\n";
	cout << "-----------------------------\n";
	for (int i = 0; i < index; ++i)
		it++;

	cout << "Name:\t" << it->name << endl;
	cout << "Gender:\t" << it->gender << endl;
	cout << "Age:\t" << it->age << endl;
	cout << "-----------------------------\n\n";
}

void remove_guest(my_container* my_guests, int index)
{
	auto it = my_guests->begin();

	for (int i = 0; i < index; ++i)
		it++;

	my_guests->erase(it);
}

float average_age(my_container* my_guests)
{
	int total_age = 0;
	int nGuests = 0;
	auto it = my_guests->begin();

	while (it != my_guests->end())
	{
		total_age += it->age;
		nGuests++;
		it++;
	}

	return (float)total_age / nGuests;
}

int main(void)
{
	my_container* my_guests = new my_container;
	read_file(my_guests);
	print_guests(my_guests);
	print_guests(my_guests, 3);
	remove_guest(my_guests, 3);
	print_guests(my_guests);
	cout << "Average age of the group is : " << average_age(my_guests) << endl;

	return 0;
}