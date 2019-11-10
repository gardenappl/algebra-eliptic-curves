#pragma once
#include <vector>
#include <string>
#include <sstream>

class LongModInt
{
private:
	std::vector<int> x;
	bool isNegative;
	bool isInfinite = false;
	std::vector<int> m;
	

	void removeZeros();
	void shiftRight();
	friend LongModInt intaddition(LongModInt number1, LongModInt number2);
	friend LongModInt intdivide(LongModInt number1, LongModInt number2);
	friend LongModInt intmultiply(LongModInt number1, LongModInt number2);
public:
	LongModInt(std::string str, std::string m);
	LongModInt(bool isInfinite);
	LongModInt();
	bool ifNegative() { return isNegative; }
	//have access to private variables
	friend std::ostream& operator <<(std::ostream& stream, LongModInt& number);
	friend bool operator ==(LongModInt& number1, LongModInt& number2);
	bool isInfinite() { return this->isInfinite; };

	//friend Arithmetic multiply(Arithmetic number1, Arithmetic number2, int module);
	//friend bool operator <(Arithmetic& number1, Arithmetic& number2);

};




