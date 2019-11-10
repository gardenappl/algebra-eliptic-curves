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
	friend LongModInt add(const LongModInt& number1, LongModInt number2);
	friend LongModInt divide(const LongModInt &number1, const LongModInt& number2);
	//returns a * b but not in mod m
	friend LongModInt multiply_non_mod(const LongModInt& number1, const LongModInt& number2);
public:
	LongModInt(std::string str, std::string m);
	LongModInt(bool isInfinite);
	LongModInt();
	//have access to private variables
	bool isNegative() const { return negative; }
	bool isInfinite() const { return this->infinite; };

	friend std::ostream& operator <<(std::ostream& stream, LongModInt& number);
	bool operator ==(const LongModInt& number2) const;

	//returns (a * b) mod m
	LongModInt operator*(const LongModInt& number2) const;
	LongModInt operator+(const LongModInt& number2) const;

	//friend Arithmetic multiply(Arithmetic number1, Arithmetic number2, int module);
	//friend bool operator <(Arithmetic& number1, Arithmetic& number2);

};




