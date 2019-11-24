#pragma once
#include <vector>
#include <string>
#include <sstream>

class LongModInt
{
private:
	LongModInt();
	LongModInt(int number, int m);
	LongModInt(int number, const std::vector<int>& m);
	LongModInt(std::vector<int> number);
	LongModInt(bool isInfinite);

	std::vector<int> x;
	bool negative;
	bool infinite = false;
	std::vector<int> m;

	void removeZeros();
	void shiftRight();
	void revert(int size);
	static LongModInt gcdExtended(const LongModInt& a, const LongModInt& b, LongModInt& x, LongModInt& y);


	static LongModInt signedAdd(LongModInt number1, LongModInt number2);
	static LongModInt signedSubtract(LongModInt number1, LongModInt number2);
	static LongModInt signedMod(const LongModInt& number1, const LongModInt& number2);
	static LongModInt signedDivide(const LongModInt& number1, const LongModInt& number2);
	static LongModInt signedMultiply(const LongModInt& number1, const LongModInt& number2);
	static LongModInt signedNeg(const LongModInt& number1);
	

public:
	LongModInt(std::string str, std::string m);
	//bool isNegative() { return negative; };
	bool isInfinite() { return this->infinite; };


	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);
	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator >=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);
	friend bool operator !=(const LongModInt& number1, const LongModInt& number2);
	

	// ~x is x^-1
	LongModInt operator ~() const;
	LongModInt operator -() const;
	LongModInt operator /(const LongModInt& number2) const;
	LongModInt operator *(const LongModInt& number2) const;
	LongModInt operator -(const LongModInt& number2) const;
	LongModInt operator +(const LongModInt& number2) const;

};




