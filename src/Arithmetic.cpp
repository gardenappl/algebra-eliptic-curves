#include "Arithmetic.h"
#include <string>
#include <iostream>

const int BASE = 10;

LongModInt::LongModInt(std::string str, std::string m)
{
	int i = 0;
	if (str[0] == '-') {
		negative = true;
		i = 1;
	}
	else negative = false;
	x.resize(str.length());
	for (; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}
	//TODO check negative module
	this->m.resize(m.length());
	for (i = 0; i < m.length(); i++) {
		this->m[i] = m[i] - '0';
	}

	LongModInt module = LongModInt(this->m);
	LongModInt number = LongModInt(this->x);

	if (number > module) {
		this->x = intremainder(number, module).x;
	}

	if (negative) {
		number = LongModInt(this->x);
		this->x = intsubtraction(module, number).x;
		negative = false;
	}
}

LongModInt::LongModInt(int number, int m)
{
	std::string str = std::to_string(number);
	std::string module = std::to_string(m);

	if (str[0] == '-') {
		negative = true;
	}
	else negative = false;
	x.resize(str.length());
	for (int i = 0; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}

	this->m.resize(module.length());
	for (int i = 0; i < module.length(); i++) {
		this->m[i] = module[i] - '0';
	}
}

LongModInt::LongModInt(std::vector<int> number)
{
	this->x = number;
	this->negative = false;
	this->infinite = false;
}

LongModInt::LongModInt(bool isInfinite)
{
	this->infinite = isInfinite;
	LongModInt();
}

LongModInt::LongModInt()
{
	negative = false;
}


void LongModInt::revert(int size)
{
	std::vector<int> updated_result;
	int i = size - 1;
	while (i >= 0) {
		updated_result.push_back(x[i]);
		i--;
	}
	x = updated_result;
}

void LongModInt::removeZeros()
{
	while (this->x.size() > 1 && this->x.front() == 0) this->x.erase(x.begin());
}

void LongModInt::shiftRight()
{
	if (x.size() == 0) {
		x.push_back(0);
		return;
	}
	x.push_back(x[x.size() - 1]);
	for (int i = x.size() - 2; i > 0; --i) x[i] = x[i - 1];
	x[0] = 0;
}

LongModInt gcdExtended(LongModInt a, LongModInt b, LongModInt& x, LongModInt& y)
{
	// Base Case 
	if (a == LongModInt(0, 0))
	{
		x = LongModInt(0, 0);
		y = LongModInt(1, 0);
		return b;
	}
	LongModInt x1, y1;
	LongModInt gcd = gcdExtended(intremainder(b, a), a, x1, y1);
	x = intsubtraction(y1, intmultiply(intdivide(b, a), x1));
	y = x1;
	return gcd;
}

std::ostream& operator<<(std::ostream& stream, const LongModInt& number)
{
	if (number.negative) stream << '-';
	for (int i = 0; i < number.x.size(); i++) {
		stream << number.x[i];
	}
	return stream;
}

bool operator <(const LongModInt& number1, const LongModInt& number2)
{
	if (number1 == number2) return false;

	if (number1.negative && !number2.negative)
		return true;

	if (!number1.negative && number2.negative)
		return false;

	if (number1.negative && number2.negative) return number2 < number1;

	if (number1.x.size() != number2.x.size()) return number1.x.size() < number2.x.size();

	//they have the same array sizes
	for (int j = 0; j < number1.x.size(); j++)
		if (number1.x[j] != number2.x[j]) return number1.x[j] < number2.x[j];

	return false;
}

bool operator <=(const LongModInt& number1, const LongModInt& number2)
{
	return (number1 < number2 || number1 == number2);
}

bool operator ==(const LongModInt& number1, const LongModInt& number2)
{
	if (number1.negative != number2.negative) return false;
	if (number1.x.size() != number2.x.size()) return false;
	for (int i = 0; i < number1.x.size(); i++)
		if (number1.x[i] != number2.x[i]) return false;
	return true;
}

bool operator >(const LongModInt& number1, const LongModInt& number2)
{
	if (number1.x.size() < number2.x.size())
		return false;
	if (number1.x.size() > number2.x.size())
		return true;
	for (int i = 0; i < number2.x.size(); i++)
		if (number1.x[i] < number2.x[i])
			return false;
		else if (number1.x[i] > number2.x[i])
			return true;
	return false;
}

bool operator >=(const LongModInt& number1, const LongModInt& number2) {
	return (number1 > number2) || (number1 == number2);
}

//TODO operator !=
LongModInt operator~(const LongModInt& number1)
{
	LongModInt x, y;
	LongModInt module(number1.m);

	LongModInt g = gcdExtended(number1, module, x, y);
	if (!(g == LongModInt(1,0)))
		std::cout << "Inverse doesn't exist";
	else
	{
		if (x > module) {
			x = intremainder(x, module);
		}
		if (x.negative) {
			x = intsubtraction(module, -x);
			x.negative = false;
		}
		LongModInt res = x;
		res.m = number1.m;
		return res;
	}
}

LongModInt operator-(const LongModInt& number1)
{
	LongModInt number2 = number1;
	number2.negative = !number1.negative;
	return number2;
}

LongModInt operator /(const LongModInt& number1, const LongModInt& number2)
{
	return LongModInt();
}

LongModInt operator *(const LongModInt& number1, const LongModInt& number2)
{
	if (number1.m != number2.m) return NULL;
	LongModInt number = intmultiply(number1, number2);
	LongModInt mod(number1.m);
	LongModInt result = intremainder(number, mod);
	result.m = number1.m;
	return result;
}

//TODO check if module1 == module2
LongModInt operator +(const LongModInt& number1, const LongModInt& number2)
{
    LongModInt number = intaddition(number1, number2);
    LongModInt mod(number1.m);
    if (number >= mod) {
		LongModInt result = intsubtraction(number, mod);
		result.m = number1.m;
		return result;
    }
	number.m = number1.m;
    return number;
}

LongModInt operator -(const LongModInt& number1, const LongModInt& number2)
{
    if (number2 > number1) {
        LongModInt number = intsubtraction(number1, number2);
        LongModInt mod(number1.m);
		LongModInt result = intaddition(number, mod);
		result.m = number1.m;
		return result;
    }
	LongModInt result = intsubtraction(number1, number2);
	result.m = number1.m;
	return result;
}


LongModInt intmultiply(LongModInt number1, LongModInt number2)
{
	LongModInt result;
	result.m = number1.m;
	int n = number1.x.size();
	int t = number2.x.size();
	int size = n + t + 1;
	result.x.resize(size);
	int c = 0;
	if (number1.negative && !number2.negative) result.negative = true;
	if (number2.negative && !number1.negative) result.negative = true;

	int shift = 0;
	int shift_iterator = 0;

	for (int i = number1.x.size() - 1; i >= 0; i--) {
		c = 0;
		shift_iterator = 0;
		for (int j = number2.x.size() - 1; j >= 0; j--) {
			int current = result.x[shift + shift_iterator] + number2.x[j] * number1.x[i] + c;
			result.x[shift + shift_iterator] = current % 10;
			c = current / 10;
			shift_iterator++;
		}
		result.x[shift + shift_iterator] = c;
		shift++;
	}
	result.revert(size);
	result.removeZeros();
	return result;
}

LongModInt intaddition(LongModInt number1, LongModInt number2)
{
    LongModInt result;
	result.m = number1.m;
    int n1 = number1.x.size();
    int n2 = number2.x.size();
	
	if (number2.negative && !number1.negative) return intsubtraction(number1, -number2);
	if (number1.negative && !number2.negative) return intsubtraction(number2, -number1);
	
    int size = (n1 > n2 ? n1 : n2) + 1;
	result.x.resize(size);

	number1.revert(n1);
	number2.revert(n2);

	int c = 0;
	int i;
	for (i = 0; i < size - 1; i++) {
        c = (i < number1.x.size() ? number1.x[i] : 0) + (i < number2.x.size() ? number2.x[i] : 0) + c;
        result.x[i] = c%10;
        c = c/10;
	}
    result.x[i] = c;
    result.revert(size);
    result.removeZeros();

    return result;
}

LongModInt intsubtraction (LongModInt number1, LongModInt number2)
{
    LongModInt result;
	result.m = number1.m;
    int n1 = number1.x.size();
    int n2 = number2.x.size();
    int size = (n1 > n2 ? n1 : n2) + 1;
	result.x.resize(size);

	if (!number1.negative && number2.negative) return intaddition(number1, -number2);
	if (number1.negative && !number2.negative) return -intaddition(-number1, number2);
	if (number1.negative && number2.negative) return intsubtraction(-number2, -number1);

	if (number2 > number1) {
            result.negative = true;
			LongModInt temp = number1;
			number1 = number2;
			number2 = temp;
    }
	number1.revert(n1);
	number2.revert(n2);

	int c = 0;
	for (int i = 0; i < size - 1; i++) {
        int number = (i < number2.x.size() ? number2.x[i] : 0);
        if (number1.x[i] + c >= number) {
            result.x[i] = number1.x[i] + c - number;
            c = 0;
        }
        else {
            result.x[i] = 10 + number1.x[i] + c - number2.x[i];
            c = -1;
        }
	}
	result.revert(size);
    result.removeZeros();
    return result;
}

LongModInt intremainder(LongModInt number1, LongModInt number2)
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0) return NULL;

	int n = number1.x.size();
	int t = number2.x.size();
	LongModInt result, remainder;
	result.m = number1.m;
	remainder.m = number1.m;
	int x = 0;
	int left = 0;
	int right = 10;
	result.x.resize(n);

	for (int i = 0; i < number1.x.size(); i++) {
		remainder.x.push_back(number1.x[i]);
		x = 0;
		left = 0;
		right = BASE;
		while (left <= right) {
			int m = (left + right) / 2;
			LongModInt mod = LongModInt(m, 0);
			LongModInt t = intmultiply(number2, mod);
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = intsubtraction(remainder, intmultiply(number2, LongModInt(x, 0)));
	}
	result.negative = number1.negative != number2.negative;
	result.removeZeros();
	return remainder;
}

LongModInt intdivide(LongModInt number1, LongModInt number2)
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0) return NULL;

	int n = number1.x.size();
	int t = number2.x.size();
	LongModInt result, remainder;
	result.m = number1.m;
	remainder.m = number1.m;
	int x = 0;
	int left = 0;
	int right = 10;
	result.x.resize(n);

	for (int i = 0; i < number1.x.size(); i++) {
		remainder.x.push_back(number1.x[i]);
		x = 0;
		left = 0;
		right = BASE;
		while (left <= right) {
			int m = (left + right) / 2;
			LongModInt mod = LongModInt(m, 0);
			LongModInt t = intmultiply(number2, mod);
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = intsubtraction(remainder, intmultiply(number2, LongModInt(x, 0)));
	}
	result.negative = number1.negative != number2.negative;
	result.removeZeros();
	return result;
}
