#pragma once

#include <limits>
#include <iostream>

using namespace std;

struct Point
{
private:
	bool infinite = false;

public:
	long x;
	long y;

	Point() = default;
	Point(long x, long y);
	static Point makeInfinite();

	bool isInfinite() const;
	bool operator==(const Point& p);
	friend ostream& operator<<(ostream& os, const Point& p);
};

//Weierstrass equation: y^2 = x^3 + Ax + B
//(long will be replaced by LongModInt)
class EllipticCurve
{
	long a;
	long b;

public:
	EllipticCurve(long p1, long p2);

	Point add(const Point& p1, const Point& p2);
	Point invert(const Point& p);
};
