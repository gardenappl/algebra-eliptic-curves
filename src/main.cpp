// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "Arithmetic.h"
#include "EllipticCurve.h"

using namespace std;

int main()
{
	LongModInt x("8", "5");
	LongModInt y("4", "5");

	LongModInt result = x / y;
	cout << result << std::endl;

	/*EllipticCurve e(-25, 0);
	cout << e.add(Point(0, 0), Point(-5, 0)) << endl;
	cout << e.add(Point(0, 0), Point(0, 0)) << endl;*/
}
