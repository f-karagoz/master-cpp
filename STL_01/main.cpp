#include <iostream>
using namespace std;

// Generic types : Templates 

template <typename T>

int size_in_bits(const T& a)
{
	return sizeof(a) * 8;
}

int main(void)
{
	cout << size_in_bits(21) << endl;	// int constant
	cout << size_in_bits('f') << endl;	// char constant
	cout << size_in_bits(32.1f) << endl;	// float constant
	cout << size_in_bits(32.1) << endl;	// double constant
	return 0;
}