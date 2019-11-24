#include "Arithmetic.h"
#include <string>
#include <iostream>
#include <cassert>
#include <limits>

const int BASE = 10;

LongModInt::LongModInt(const std::string& str, const std::string& m)
{
	int i = 0;

	//Don't let users create negative integers
	if(str[0] == '-')
		throw std::invalid_argument("Integers can't be negative in modular arithmetic.");
	negative = false;
//	if (str[0] == '-') {
//		negative = true;
//		i = 1;
//	}
//	else negative = false;

	x.resize(str.length());
	for (; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}
	if(m.empty() || (m == "0"))
		throw std::invalid_argument("Modulo can't be 0.");
	if(m[0] == '-')
		throw std::invalid_argument("Modulo can't be negative.");
	this->m.resize(m.length());
	for (i = 0; i < m.length(); i++) {
		this->m[i] = m[i] - '0';
	}

	LongModInt module = LongModInt(this->m);
	LongModInt number = LongModInt(this->x);

	if (number > module) {
		this->x = signedMod(number, module).x;
	}

	if (negative) {
		number = LongModInt(this->x);
		this->x = signedSubtract(module, number).x;
		negative = false;
	}
}

LongModInt::LongModInt(const std::string& str, const std::vector<int>& m)
	: m(m), negative(false)
{
	int i = 0;

	//Don't let users create negative integers
	if(!str.empty() && str[0] == '-')
		throw std::invalid_argument("Integers can't be negative in modular arithmetic.");
	negative = false;

	x.resize(str.length());
	for (; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}

	LongModInt module = LongModInt(this->m);
	LongModInt number = LongModInt(this->x);

	if (number > module) {
		this->x = signedMod(number, module).x;
	}

	if (negative) {
		number = LongModInt(this->x);
		this->x = signedSubtract(module, number).x;
		negative = false;
	}
}



LongModInt::LongModInt(long long number, long long m)
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

LongModInt::LongModInt(long long number)
		: LongModInt(number, 0)
{
}

LongModInt::LongModInt(long long number, const std::vector<int>& m)
	: m(m)
{
	std::string str = std::to_string(number);
	int i = 0;

	//Don't let users create negative integers
	if(str[0] == '-')
		throw std::invalid_argument("Integers can't be negative in modular arithmetic.");
	negative = false;
//	if (str[0] == '-') {
//		negative = true;
//		i = 1;
//	}
//	else negative = false;

	x.resize(str.length());
	for (; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}

	LongModInt module = LongModInt(this->m);
	LongModInt longNumber = LongModInt(this->x);

	if (longNumber > module) {
		this->x = signedMod(longNumber, module).x;
	}

	if (negative) {
		longNumber = LongModInt(this->x);
		this->x = signedSubtract(module, longNumber).x;
		negative = false;
	}
}

LongModInt::LongModInt(const std::vector<int>& number)
	: x(number), m(std::vector<int>()), negative(false)
{
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

LongModInt LongModInt::gcdExtended(const LongModInt& a, const LongModInt& b, LongModInt& x, LongModInt& y)
{
	// Base Case 
	if (a == LongModInt(0, 0))
	{
		x = LongModInt(0, 0);
		y = LongModInt(1, 0);
		return b;
	}
	LongModInt x1, y1;
	LongModInt gcd = gcdExtended(signedMod(b, a), a, x1, y1);
	x = signedSubtract(y1, signedMultiply(signedDivide(b, a), x1));
	y = x1;
	return gcd;
}

std::ostream& operator<<(std::ostream& stream, const LongModInt& number)
{
	if (number.negative) stream << '-';
	for (int i = 0; i < number.x.size(); i++) {
		stream << number.x[i];
	}

//	stream << "(mod ";
//	for (int i = 0; i < number.m.size(); i++) {
//		stream << number.m[i];
//	}
//	stream << ")";

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
	return !(number1 > number2);
}

bool operator >=(const LongModInt& number1, const LongModInt& number2)
{
	return !(number1 < number2);
}

bool operator ==(const LongModInt& number1, const LongModInt& number2)
{
	if (number1.negative != number2.negative) return false;
	if (number1.x.size() != number2.x.size()) return false;
	for (int i = 0; i < number1.x.size(); i++)
		if (number1.x[i] != number2.x[i]) return false;
	return true;
}

bool operator !=(const LongModInt& number1, const LongModInt& number2)
{
	return !(number1 == number2);
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

LongModInt LongModInt::operator~() const
{
	LongModInt x, y;
	LongModInt module(this->m);

	LongModInt g = gcdExtended(*this, module, x, y);
	if (!(g == LongModInt(1,0)))
		std::cout << "Inverse doesn't exist";
	else
	{
		if (x > module) {
			x = signedMod(x, module);
		}
		if (x.negative) {
			x = signedSubtract(module, -x);
			x.negative = false;
		}
		LongModInt res = x;
		res.m = this->m;
		return res;
	}
	return LongModInt(-1, 0);
}

LongModInt LongModInt::operator-() const
{
	return LongModInt(0, this->m) - *this;
}

LongModInt LongModInt::operator/(const LongModInt& number2) const
{
	if(!checkEqualMods(*this, number2))
		throw std::invalid_argument("Moduli must be equal.");

	LongModInt x, y;
	LongModInt module(this->m);
	LongModInt inv = ~number2;
	if (inv == LongModInt(-1, 0)) {
		std::cout << "Division not defined";
		return LongModInt(-1, 0);
	}
	else
		return inv * *this;
}

LongModInt LongModInt::operator *(const LongModInt& number2) const
{
	if(!checkEqualMods(*this, number2))
		throw std::invalid_argument("Moduli must be equal.");

	LongModInt number = signedMultiply(*this, number2);
	LongModInt mod(this->m);
	LongModInt result = signedMod(number, mod);
	result.m = this->m;
	return result;
}

LongModInt LongModInt::operator +(const LongModInt& number2) const
{
	if(!checkEqualMods(*this, number2))
		throw std::invalid_argument("Moduli must be equal.");

    LongModInt number = signedAdd(*this, number2);
    LongModInt mod(this->m);
    if (number >= mod) {
		LongModInt result = signedSubtract(number, mod);
		result.m = this->m;
		return result;
    }
	number.m = this->m;
    return number;
}

LongModInt LongModInt::operator-(const LongModInt& number2) const
{
	if(!checkEqualMods(*this, number2))
		throw std::invalid_argument("Moduli must be equal.");

    if (number2 > *this) {
        LongModInt number = signedSubtract(*this, number2);
        LongModInt mod(this->m);
		LongModInt result = signedAdd(number, mod);
		result.m = this->m;
		return result;
    }
	LongModInt result = signedSubtract(*this, number2);
	result.m = this->m;
	return result;
}


LongModInt LongModInt::signedMultiply(const LongModInt& number1, const LongModInt& number2)
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

LongModInt LongModInt::signedAdd(LongModInt number1, LongModInt number2)
{
    LongModInt result;
	result.m = number1.m;
    int n1 = number1.x.size();
    int n2 = number2.x.size();
	
	if (number2.negative && !number1.negative) return signedSubtract(number1, signedNeg(number2));
	if (number1.negative && !number2.negative) return signedSubtract(number2, signedNeg(number1));
	
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

LongModInt LongModInt::signedSubtract (LongModInt number1, LongModInt number2)
{
	LongModInt result;
	if (number2 > number1) {
		result.negative = true;
		LongModInt temp = number1;
		number1 = number2;
		number2 = temp;
	}

	result.m = number1.m;
    int n1 = number1.x.size();
    int n2 = number2.x.size();
    int size = (n1 > n2 ? n1 : n2) + 1;
	result.x.resize(size);

	if (!number1.negative && number2.negative) return signedAdd(number1, signedNeg(number2));
	if (number1.negative && !number2.negative) return signedNeg(signedAdd(signedNeg(number1), number2));
	if (number1.negative && number2.negative) return signedSubtract(signedNeg(number2), signedNeg(number1));

	if (number1.x.size() > 1) number1.revert(n1);
	if (number2.x.size() > 1) number2.revert(n2);

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

LongModInt LongModInt::signedMod(const LongModInt& number1, const LongModInt& number2)
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0)
		throw std::invalid_argument("Modulo can't be 0.");

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
			LongModInt mod = LongModInt(m);
			LongModInt t = signedMultiply(number2, mod);
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = signedSubtract(remainder, signedMultiply(number2, LongModInt(x, 0)));
	}
	result.negative = number1.negative != number2.negative;
	result.removeZeros();
	return remainder;
}

LongModInt LongModInt::signedDivide(const LongModInt& number1, const LongModInt& number2)
{
	//cannot divide by zero
	if (number2.x.size() == 1 && number2.x[0] == 0)
		throw std::invalid_argument("Can't divide by 0");

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
			LongModInt t = signedMultiply(number2, mod);
			if (t <= remainder) {
				x = m;
				left = m + 1;
			}
			else right = m - 1;
		}
		result.x[i] = x;
		remainder = signedSubtract(remainder, signedMultiply(number2, LongModInt(x, 0)));
	}
	result.negative = number1.negative != number2.negative;
	result.removeZeros();
	return result;
}

LongModInt LongModInt::signedNeg(const LongModInt& number1)
{
	LongModInt number2 = number1;
	number2.negative = !number1.negative;
	return number2;
}

bool LongModInt::checkEqualMods(const LongModInt& number1, const LongModInt &number2)
{
	return number1.m == number2.m;
}

std::vector<int> LongModInt::getMod() const
{
	return m;
}



//Operators with strings, for convenience

LongModInt operator*(const std::string& number, const LongModInt& number2)
{
	return LongModInt(number, number2.m) * number2;
}

LongModInt operator/(const std::string&  number, const LongModInt& number2)
{
	return LongModInt(number, number2.m) / number2;
}

LongModInt operator+(const std::string& number, const LongModInt& number2)
{
	return LongModInt(number, number2.m) + number2;
}

LongModInt operator-(const std::string& number, const LongModInt& number2)
{
	return LongModInt(number, number2.m) - number2;
}


LongModInt LongModInt::operator/(const std::string& number2) const
{
	return *this / LongModInt(number2, this->m);
}

LongModInt LongModInt::operator*(const std::string& number2) const
{
	return *this * LongModInt(number2, this->m);
}

LongModInt LongModInt::operator-(const std::string& number2) const
{
	return *this - LongModInt(number2, this->m);
}

LongModInt LongModInt::operator+(const std::string& number2) const
{
	return *this + LongModInt(number2, this->m);
}

bool LongModInt::operator==(const std::string& number2) const
{
	return *this == LongModInt(number2, this->m);
}

bool LongModInt::operator!=(const std::string& number2) const
{
	return *this != LongModInt(number2, this->m);
}