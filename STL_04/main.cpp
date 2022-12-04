/**
* Title: Birthday Party : vector and list usage example
* Author: Furkan Karagoz
* Instructor: Eduardo Corpena
* Date: 4 / 12 / 2022
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
	cout << "--  Container Content End  --\n";
}

int main(void)
{
	my_container* my_guests = new my_container;
	read_file(my_guests);
	print_guests(my_guests);
	return 0;
}