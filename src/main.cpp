// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "Arithmetic.h"
#include "EllipticCurve.h"

using namespace std;

int main()
{
	LongModInt x("4", "25");
	LongModInt y("2", "25");
	LongModInt a;
	LongModInt b;

	LongModInt result = gcdExtended(x, y, a, b);

	cout << result << std::endl;

	EllipticCurve e(-25, 0);
	cout << e.add(Point(0, 0), Point(-5, 0)) << endl;
	cout << e.add(Point(0, 0), Point(0, 0)) << endl;
}
