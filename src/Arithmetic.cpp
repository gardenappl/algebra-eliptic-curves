#include <cassert>
#include "Arithmetic.h"

void LongModInt::removeZeros()
{
	while ((x.size() > 1) && (this->x.back() == 0)) x.pop_back();
	if (x.size() == 1 && x[0] == 0) negative = false;
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

LongModInt::LongModInt(std::string str, std::string m)
{
	if (str[0] == '-') {
		negative = true;
	}
	else negative = false;
	x.resize(str.length());
	for (int i = 0; i < str.length(); i++) {
		x[i] = str[i] - '0';	
	}

	this->m.resize(m.length());
	for (int i = 0; i < m.length(); i++) {
		this->m[i] = m[i] - '0';
	}
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



//returning remainder - not ready
//Arithmetic intdivide(Arithmetic number1, Arithmetic number2)
//{
//	int n = number1.x.size();
//	int t = number2.x.size();
//	Arithmetic result, current;
//	Arithmetic quotient;
//	int x = 0;
//	int left = 0;
//	int right = 10;
//	quotient.x.resize(n - t);
//	result.x.resize(n);
//	//cannot divide by zero
//	//if (number2.x.size() == 1 && number2.x[0] == 0)
//	for (int i = n - 1; i >= 0; --i) {
//		current.shiftRight();
//		current.x[0] = number1.x[i];
//		current.removeZeros();
//		x = 0;
//		left = 0;
//		right = 10;
//		while (left <= right) {
//			int m = (left + 10) / 2;
//			Arithmetic t = intmultiply(number1, number1.m);
//			if (t <= current) {
//				x = m;
//				l = m + 1;
//			}
//			else right = m - 1;
//		}
//		result.x[i] = x;
//		current = current - intmultiply();
//	}
//
//}

std::ostream& operator<<(std::ostream& stream, LongModInt& number)
{
	if (number.negative) stream << '-';
	for (int i = 0; i < number.x.size(); i++) {
		stream << number.x[i];
	}
	return stream;
}

bool LongModInt::operator==(const LongModInt& number2) const
{
	if (this->negative != number2.negative) return false;
	if (this->x.size() != number2.x.size()) return false;
	for (int i = 0; i < this->x.size(); i++)
		if (this->x[i] != number2.x[i]) return false;
	return true;
}

//Arithmetic multiply(Arithmetic number1, Arithmetic number2, int module)
//{
//	
//}

LongModInt multiply_non_mod(const LongModInt& number1, const LongModInt& number2)
{
	LongModInt result;
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
		for (int j = number2.x.size() - 1; j >=0; j--) {
			int current = result.x[shift + shift_iterator] + number2.x[j] * number1.x[i] + c;
			result.x[shift + shift_iterator] = current % 10;
			c = current / 10;
			shift_iterator++;
		}
		result.x[shift + shift_iterator] = c;
		shift++;
	}

	result.removeZeros();
	return result;
}

LongModInt add(const LongModInt& number1, LongModInt number2)
{
    LongModInt result;
    int n1 = number1.x.size();
    int n2 = number2.x.size();
    int size = n1 + 1;
	result.x.resize(size);

    if (n1 > n2) {
        int siz = n1;
        number2.x.resize(siz);
        for (int i = n1-1; i >= 0; i--) {
            if (n2 != 0) {
                number2.x[i] = number2.x[n2 - 1];
                n2--;
            }
            else {
            number2.x[i] = 0;
        }
    }
    }
    int c = 0;
    for (int i = 0; i < n1; i++) {
        int sum = number1.x[i] + number2.x[i] + c;
        result.x[i] = sum % 10;//for b!=10 it will be mod b
        if ((number1.x[i] + number2.x[i] + c) < 10) c = 0;
        else c = 1;
    }
    result.x[n1 + 1] = c;
    result.removeZeros();
    return result;

}

//This should return (a * b) % mod m
LongModInt LongModInt::operator*(const LongModInt &number2) const
{
	assert(this->m == number2.m);
	return multiply_non_mod(*this, number2);
}

LongModInt LongModInt::operator+(const LongModInt &number2) const
{
	assert(this->m == number2.m);
	return add(*this, number2);
}


//bool operator<(Arithmetic& number1, Arithmetic& number2)
//{
//	if (number1 == number2) return false;
//
//	if (number1.isNegative && !number2.isNegative)
//		return true;
//
//	if (!number1.isNegative && number2.isNegative)
//		return false;
//
//	if (number1.isNegative && number2.isNegative) return number2 < number1;
//
//
//	for (int i = number1.x.size() - 1; i >= 0; --i) {
//		if (number1.x[i] != number2.x[i]) return
//
//}


