#pragma once

#include <limits>
#include <iostream>
#include "Arithmetic.h"

using namespace std;

struct Point
{
private:
	bool infinite = false;

public:
	LongModInt x;
	LongModInt y;

	Point() = default;
	Point(const LongModInt& x, const LongModInt& y);
	static Point makeInfinite(); //"constructor" for infinite point

	bool isInfinite() const;
	bool operator==(const Point& p);
	friend ostream& operator<<(ostream& os, const Point& p);
};

//Weierstrass equation: y^2 = x^3 + Ax + B
class EllipticCurve
{
	LongModInt a;
	LongModInt b;

public:
	//to-do: check if modulo is prime?
	EllipticCurve(const LongModInt& a, const LongModInt& b);
	EllipticCurve(const std::string& a, const std::string& b, const std::string& mod);

	Point add(const Point& p1, const Point& p2) const;
	Point add(const std::pair<std::string, std::string>& p1, const std::pair<std::string, std::string>& p2) const;
	Point invert(const Point& p) const;
	bool isVaild(const Point& p) const;
};
