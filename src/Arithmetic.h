#pragma once
#include <vector>
#include <string>
#include <sstream>

class LongModInt
{
private:
	LongModInt(int number, int m);
	LongModInt(std::vector<int> number);
	LongModInt(bool isInfinite);
	LongModInt();

	std::vector<int> x;
	bool negative;
	bool infinite = false;
	std::vector<int> m;

	void removeZeros();
	void shiftRight();
	void revert(int size);

	friend LongModInt intaddition(LongModInt number1, LongModInt number2);
	friend LongModInt intsubtraction(LongModInt number1, LongModInt number2);
	friend LongModInt intdivide(LongModInt number1, LongModInt number2);
	friend LongModInt intmultiply(LongModInt number1, LongModInt number2);

public:
	LongModInt(std::string str, std::string m);
	bool isNegative() { return negative; };
	bool isInfinite() { return this->infinite; };

	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);
	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator >=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);

	friend LongModInt operator ~(const LongModInt& number1);
	friend LongModInt operator -(const LongModInt& number1);
	friend LongModInt operator /(const LongModInt& number1, const LongModInt& number2);
	friend LongModInt operator *(const LongModInt& number1, const LongModInt& number2);
	friend LongModInt operator -(const LongModInt& number1, const LongModInt& number2);
	friend LongModInt operator +(const LongModInt& number1, const LongModInt& number2);

};




