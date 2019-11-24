// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "Arithmetic.h"
#include "EllipticCurve.h"

using namespace std;

int gcdExtended(int a, int b, int* x, int* y)
{
	// Base Case 
	if (a == 0)
	{
		*x = 0, * y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call 
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of recursive 
	// call 
	std::cout << a << " " << b << " " << x1 << " " << y1 << std::endl;
	*x = y1 - (b / a) * x1;
	*y = x1;
	std::cout << *x << " " << *y << endl;
	return gcd;
}

int main()
{
	LongModInt x("10", "17");
	LongModInt y("2", "25");

	LongModInt result = ~x;
	cout << result << std::endl;

	/*EllipticCurve e(-25, 0);
	cout << e.add(Point(0, 0), Point(-5, 0)) << endl;
	cout << e.add(Point(0, 0), Point(0, 0)) << endl;*/
}
