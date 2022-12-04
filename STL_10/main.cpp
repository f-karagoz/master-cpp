/*
* Title: Stack / queue challenge : Web url
* Author: Furkan Karagoz
* Instructor: Eduardo Corpeno
* Date: 5 / 12 / 2022
*
* Visited website urls.
* Purpose: implement a back button
* Challenge tasks:	Keep a history of the URLs visited each time the back button is pressed
*					The additional history is cleared when a new address is entered
* Test conditions:	Enter a series of URLs
*					Go back some times
*					Go forward new URL
*					Assert the forward stack is emoty
*					Bo back few URLs to make sure back stack is not empty
*/

#include <iostream>
#include <stack>
using namespace std;

int main(void)
{
	stack<string> back_stack;
	stack<string> forward_stack;
	string temp;

	while (temp != "exit")
	{
		cout << "[1] Visit URL\t";
		if (back_stack.size() > 1)
			cout << "[2] Back\t";
		if (forward_stack.empty() != 1)
			cout << "[3] Forward";
		cout << endl;

		cin >> temp;
		if (temp == "exit")
			break;
		else if (temp == "1")
		{
			cout << "Enter URL: ";
			cin >> temp;
			back_stack.push(temp);

			// Clear the forward stack when new URL entered
			//while (forward_stack.empty() != 1)
			//	forward_stack.pop();

			// Default constructor and assignment operator called to clear
			forward_stack = stack<string>();	
		}
		else if (temp == "2" && back_stack.size() > 1)
		{
			cout << "Going back..." << endl;
			forward_stack.push(back_stack.top());
			back_stack.pop();
		}
		else if (temp == "3" && forward_stack.empty() != 1)
		{
			cout << "Going forward..." << endl;
			back_stack.push(forward_stack.top());
			forward_stack.pop();
		}
		else
			cout << "Invalid entry!" << endl;

		if (back_stack.empty() != 1)
			cout << "Current URL: " << back_stack.top() << endl;
	}

	return 0;
}