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

	LongModInt result = x / y;
	cout << x << " / " << y << " = " << result << std::endl;

	result = x * y;
	cout << x << " * " << y << " = " << result << std::endl;

	result = x + y;
	cout << x << " + " << y << " = " << result << std::endl;

	result = x - y;
	cout << x << " - " << y << " = " << result << std::endl;

	result = x - y + y;
	cout << x << " - " << y << " + " << y << " = " << result << std::endl;

	bool boolResult = x < y;
	cout << x << " < " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x > y;
	cout << x << " > " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x == y;
	cout << x << " == " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x <= y;
	cout << x << " <= " << y << " ? " << boolalpha << boolResult << std::endl;

	EllipticCurve e(-25, 0);
	cout << e.add(Point(0, 0), Point(-5, 0)) << endl;
	cout << e.add(Point(0, 0), Point(0, 0)) << endl;
}
