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
	LongModInt(const std::string& str, const std::string& m);
	LongModInt(const std::string& str, const std::vector<int>& m);
	//bool isNegative() { return negative; };
	static bool checkEqualMods(const LongModInt& number1, const LongModInt& number2);
	std::vector<int> getMod() const;


	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);
	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator >=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);
	friend bool operator !=(const LongModInt& number1, const LongModInt& number2);

	//TO-DO: more comparison functions, if needed
	bool operator !=(const std::string&) const;
	bool operator ==(const std::string&) const;

	// ~x is x^-1
	LongModInt operator ~() const;
	LongModInt operator -() const;
	LongModInt operator /(const LongModInt& number2) const;
	LongModInt operator *(const LongModInt& number2) const;
	LongModInt operator -(const LongModInt& number2) const;
	LongModInt operator +(const LongModInt& number2) const;

	LongModInt operator /(const std::string& number2) const;
	LongModInt operator *(const std::string& number2) const;
	LongModInt operator -(const std::string& number2) const;
	LongModInt operator +(const std::string& number2) const;

	friend LongModInt operator /(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator *(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator -(const std::string& number1, const LongModInt& number2);
	friend LongModInt operator +(const std::string& number1, const LongModInt& number2);
};




