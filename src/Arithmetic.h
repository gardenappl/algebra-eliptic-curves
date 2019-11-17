#pragma once
#include <vector>
#include <string>
#include <sstream>

class LongModInt
{
private:
	std::vector<int> x;
	bool negative;
	bool infinite = false;
	std::vector<int> m;


	void removeZeros();
	void shiftRight();
	void revert(int size);
	

public:
	LongModInt(std::string str, std::string m);
	LongModInt(int number, int m);
	LongModInt(std::vector<int> number);
	LongModInt(bool isInfinite);
	LongModInt();
	bool isNegative() { return negative; }

	friend std::ostream& operator <<(std::ostream& stream, const LongModInt& number);
	friend bool operator >(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <(const LongModInt& number1, const LongModInt& number2);
	friend bool operator <=(const LongModInt& number1, const LongModInt& number2);
	friend bool operator ==(const LongModInt& number1, const LongModInt& number2);
	friend LongModInt intaddition(LongModInt number1, LongModInt number2);
	friend LongModInt intsubtraction(LongModInt number1, LongModInt number2);
	friend LongModInt intdivide(LongModInt number1, LongModInt number2);
	friend LongModInt intmultiply(LongModInt number1, LongModInt number2);

	bool isInfinite() { return this->infinite; };

};




