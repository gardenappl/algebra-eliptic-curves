#include <iostream>
#include <cmath>
#include "ModArithmetic.h"
#include "EllipticCurve.h"
#include "Algorithms.h"

using namespace std;

int main()
{
	LongInt a("2");
	LongInt b("-45");
	cout << (a - b) << std::endl;
	cout << (b - a) << std::endl;
	cout << (a + b) << std::endl;

	LongInt c("21");
	LongInt d("3");
	cout << (d / c) << std::endl;
	cout << (c / d) << std::endl;


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

	cout << e.add({ "1", "3" }, { "1", "4" }) << endl;
//	cout << e.add({ "6", "1" }, { "1", "4" }) << endl;
//	cout << e.add({ "1", "4" }, { "6", "1" }) << endl;

	cout << e.integerTimesPoint({ "1", "4" }, 13);

	eulerCarmichaelTest();
}
