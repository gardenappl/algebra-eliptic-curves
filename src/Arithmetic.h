#pragma once
#include <vector>
#include <string>
#include <sstream>

class LongModInt
{
private:
	LongModInt(long long number);
	LongModInt(long long number, long long m);
	LongModInt(long long number, const std::vector<int>& m);
	explicit LongModInt(const std::vector<int>& number);

	std::vector<int> x;
	bool negative;
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
	LongModInt();
	LongModInt(std::string str, std::string m);
	//bool isNegative() { return negative; };


	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);
	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator >=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);
	friend bool operator !=(const LongModInt& number1, const LongModInt& number2);

	//TO-DO: more comparison functions, if needed
	bool operator !=(long long number2) const;
	bool operator ==(long long number2) const;

	// ~x is x^-1
	LongModInt operator ~() const;
	LongModInt operator -() const;
	LongModInt operator /(const LongModInt& number2) const;
	LongModInt operator *(const LongModInt& number2) const;
	LongModInt operator -(const LongModInt& number2) const;
	LongModInt operator +(const LongModInt& number2) const;

	LongModInt operator /(long long number2) const;
	LongModInt operator *(long long number2) const;
	LongModInt operator -(long long number2) const;
	LongModInt operator +(long long number2) const;

	friend LongModInt operator /(long long number1, const LongModInt& number2);
	friend LongModInt operator *(long long number1, const LongModInt& number2);
	friend LongModInt operator -(long long number1, const LongModInt& number2);
	friend LongModInt operator +(long long number1, const LongModInt& number2);
};




