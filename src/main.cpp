// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "Arithmetic.h"
#include "EllipticCurve.h"

using namespace std;

int main()
{
	LongModInt x("15", "100");
	LongModInt y("20", "100");
	LongModInt result = intsubtraction(x, y);

	cout << result << std::endl;

	EllipticCurve e(-25, 0);
	cout << e.add(Point(0, 0), Point(-5, 0)) << endl;
	cout << e.add(Point(0, 0), Point(0, 0)) << endl;
}
