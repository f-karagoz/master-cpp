/*
* Title: Stack / queue example : Web url
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*
* Visited website urls.
* Purpose: implement a back button
*/

#include <iostream>
#include <stack>
using namespace std;

int main(void)
{
	stack<string> back_stack;
	string temp;

	while (temp != "exit")
	{
		cout << "[1] Visit URL\t[2] Back" << endl;
		cin >> temp;
		if (temp == "exit")
			break;
		if (temp == "1")
		{
			cout << "Enter URL: ";
			cin >> temp;
			back_stack.push(temp);
		}
		else if (temp == "2")
		{
			cout << "Going back..." << endl;
			back_stack.pop();
		}
		if (back_stack.empty())
			break;
		cout << "Current URL: " << back_stack.top() << endl;
	}

	return 0;
}