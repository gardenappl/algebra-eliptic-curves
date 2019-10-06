#pragma once
#include <vector>
#include <string>
#include <sstream>

class Arithmetic
{
private:
	std::vector<int> x;
	bool isNegative;
	int m;

	void removeZeros();
	void shiftRight();
	friend Arithmetic intdivide(Arithmetic number1, Arithmetic number2);
	friend Arithmetic intmultiply(Arithmetic number1, Arithmetic number2);
public:
	Arithmetic(std::string str, int m);
	Arithmetic();
	bool ifNegative() { return isNegative; }
	//have access to private variables
	friend std::ostream& operator <<(std::ostream& stream, Arithmetic& number);
	friend bool operator ==(Arithmetic& number1, Arithmetic& number2);
	
	//friend Arithmetic multiply(Arithmetic number1, Arithmetic number2, int module);
	//friend bool operator <(Arithmetic& number1, Arithmetic& number2);
	
};




