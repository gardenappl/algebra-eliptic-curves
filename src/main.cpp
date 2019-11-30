// Long modular arithmetic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "ModArithmetic.h"
#include "EllipticCurve.h"
#include "Algorithms.h"

using namespace std;

int main()
{
	ModField f("7");
	LongModInt x("5", &f);
	LongModInt y("4", &f);

	LongModInt result = x - y;
	cout << x << " - " << y << " = " << result << std::endl;

	result = x - y + y;
	cout << x << " - " << y << " + " << y << " = " << result << std::endl;

	result = x * y;
	cout << x << " * " << y << " = " << result << std::endl;

	result = x + y;
	cout << x << " + " << y << " = " << result << std::endl;

	result = x / y;
	cout << x << " / " << y << " = " << result << std::endl;

	result = ~y;
	cout << y << " ^ -1 = " << result << std::endl;

	result = x / y * y;
	cout << x << " / " << y << " * " << y << " = " << result << std::endl;

	bool boolResult = x < y;
	cout << x << " < " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x > y;
	cout << x << " > " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x == y;
	cout << x << " == " << y << " ? " << boolalpha << boolResult << std::endl;

	boolResult = x <= y;
	cout << x << " <= " << y << " ? " << boolalpha << boolResult << std::endl;

	result = pow(x, y);
	cout << x << " ^ " << y << " = " << result << std::endl;
  
	//y^2 = x^3 + 3x + 5 (mod 7)
	ModField eField("7");
	EllipticCurve e("3", "5", &eField);
	cout << e.add({"1", "4"}, {"1", "4"}) << endl;

	cout << e.add({"6", "1"}, {"4", "5"}) << endl;
	cout << e.add({"4", "5"}, {"6", "1"}) << endl;

	try
	{
		cout << e.add({"0", "0"}, {"0", "0"}) << endl;
	}
	catch(std::invalid_argument e)
	{
		cout << e.what() << endl;
	}
}
