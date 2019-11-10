// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Arithmetic.h"
using namespace std;

int main()
{
	LongModInt x("23", "100");
	LongModInt y("1234", "100");
	LongModInt result = intmultiply(x, y);

	cout << result << std::endl;
	LongModInt result2 = intaddition(x, y);
	cout << result2 << std::endl;
}
