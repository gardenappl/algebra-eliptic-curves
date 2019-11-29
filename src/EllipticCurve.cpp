#include <cmath>
#include "EllipticCurve.h"

using namespace std;

Point::Point(const LongModInt& x, const LongModInt& y)
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
	else if(this->isInfinite())
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


EllipticCurve::EllipticCurve(const LongModInt& a, const LongModInt& b)
	: a(a), b(b)
{
	if(!LongModInt::checkEqualMods(a, b))
		throw std::invalid_argument("Moduli must be equal.");

	if("4" * a * a * a + "27" * b * b == "0")
		throw std::invalid_argument("Discriminant must be not equal to 0");
}


EllipticCurve::EllipticCurve(const std::string& a, const std::string& b, const std::string& mod)
		: a(LongModInt(a, mod)), b(LongModInt(b, mod))
{
	if("4" * this->a * this->a * this->a + "27" * this->b * this->b == "0")
		throw std::invalid_argument("Discriminant must be not equal to 0");
}

Point EllipticCurve::add(const Point& p1, const Point& p2) const
{
	if(!isVaild(p1))
		throw std::invalid_argument("Point 1 is not on the elliptic curve.");
	if(!isVaild(p2))
		throw std::invalid_argument("Point 2 is not on the elliptic curve.");
	if(p1.isInfinite())
		return p2;
	if(p2.isInfinite())
		return p1;

	if(p1.x != p2.x)
	{
		LongModInt m = (p2.y - p1.y) / (p2.x - p1.x);
		LongModInt x3 = m * m - p1.x - p2.x;
		return Point(x3, m * (p1.x - x3) - p1.y);
	}
	else if(p1.y != p2.y)
	{
		return Point::makeInfinite();
	}
	else
	{
		//Points are equal
		if(p1.y != "0")
		{
			LongModInt m = ("3" * p1.x * p1.x + a) / ("2" * p1.y);
			LongModInt x3 = m * m - "2" * p1.x;
			return Point(x3, m * (p1.x - x3) - p1.y);
		}
		else
		{
			return Point::makeInfinite();
		}
	}
}

Point EllipticCurve::add(const std::pair<std::string, std::string> &p1,
                         const std::pair<std::string, std::string> &p2) const
{
	Point point1(LongModInt(p1.first, a.getMod()), LongModInt(p1.second, a.getMod()));
	Point point2(LongModInt(p2.first, a.getMod()), LongModInt(p2.second, a.getMod()));
	return add(point1, point2);
}

Point EllipticCurve::invert(const Point &p) const
{
	if(p.isInfinite())
		return p;
	else
		return Point(p.x, -p.y);
}

bool EllipticCurve::isVaild(const Point &p) const
{
	return p.isInfinite() || p.y * p.y == p.x * p.x * p.x + a * p.x + b;
}