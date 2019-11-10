#include <cmath>
#include "EllipticCurve.h"

using namespace std;

Point::Point(long x, long y)
	: x(x), y(y)
{}

Point Point::makeInfinite()
{
	Point p;
	p.infinite = true;
	return p;
}

bool Point::isInfinite() const
{
	return this->infinite;
}

bool Point::operator==(const Point &p)
{
	if(p.isInfinite())
		return this->isInfinite();
	if(!this->isInfinite())
		return false;
	return this->x == p.x && this->y == p.y;
}

ostream& operator<<(ostream& os, const Point& p)
{
	if(p.isInfinite())
		os << "(inf)";
	else
		os << '(' << p.x << ", " << p.y << ")";
	return os;
}


EllipticCurve::EllipticCurve(long p1, long p2)
	: a(p1), b(p2)
{}

Point EllipticCurve::add(const Point& p1, const Point& p2)
{
	if(p1.isInfinite())
		return p2;
	if(p2.isInfinite())
		return p1;

	if(p1.x != p2.x)
	{
		long m = (p2.y - p1.y) / (p2.x - p1.x);
		long x3 = m * m - p1.x - p2.x;
		return Point(x3, m * (p1.x - x3) - p1.y);
	}
	else if(p1.y != p2.y)
	{
		return Point::makeInfinite();
	}
	else
	{
		//Points are equal
		if(p1.y != 0)
		{
			long m = (3 * p1.x * p1.x + a) / (2 * p1.y);
			long x3 = m * m - 2 * p1.x;
			return Point(x3, m * (p1.x - x3) - p1.y);
		}
		else
		{
			return Point::makeInfinite();
		}
	}
}

Point EllipticCurve::invert(const Point &p)
{
	if(p.isInfinite())
		return p;
	else
		return Point(p.x, -p.y);
}