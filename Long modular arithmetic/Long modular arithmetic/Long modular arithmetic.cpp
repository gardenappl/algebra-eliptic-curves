// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Arithmetic.h"
using namespace std;

int main()
{
	Arithmetic x("23", 100);
	Arithmetic y("1234", 100);
	Arithmetic result = intmultiply(x, y);

	cout << result;
}
