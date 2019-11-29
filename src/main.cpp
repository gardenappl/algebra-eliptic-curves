// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "Arithmetic.h"
#include "EllipticCurve.h"

using namespace std;

int main()
{
	LongModInt x("2", "17");
	LongModInt y("13", "17");

	LongModInt result = x - y;
	cout << x << " - " << y << " = " << result << std::endl;

	result = x - y + y;
	cout << x << " - " << y << " + " << y << " = " << result << std::endl;

	result = x * y;
	cout << x << " * " << y << " = " << result << std::endl;

	result = x + y;
	cout << x << " + " << y << " = " << result << std::endl;

	result = x * y;
	cout << x << " * " << y << " = " << result << std::endl;

	bool boolResult = x < y;
	cout << x << " < " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x > y;
	cout << x << " > " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x == y;
	cout << x << " == " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x <= y;
	cout << x << " <= " << y << " ? " << boolalpha << boolResult << std::endl;

	//y^2 = x^3 + 3x + 5 (mod 7)
	EllipticCurve e("3", "5", "7");
	cout << e.add({"1", "4"}, {"1", "4"}) << endl;

	try {
		cout << e.add({"0", "0"}, {"0", "0"}) << endl;
	}
	catch(std::invalid_argument e)
	{
		cout << e.what() << endl;
	}
}
