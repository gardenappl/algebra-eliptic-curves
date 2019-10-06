#include "Arithmetic.h"

void Arithmetic::removeZeros()
{
	while ((x.size() > 1) && (this->x.back() == 0)) x.pop_back();
	if (x.size() == 1 && x[0] == 0) isNegative = false;
}

void Arithmetic::shiftRight()
{
	if (x.size == 0) {
		x.push_back(0);
		return;
	}
	x.push_back(x[x.size() - 1]);
	for (int i = x.size() - 2; i > 0; --i) x[i] = x[i - 1];
	x[0] = 0;
}

Arithmetic::Arithmetic(std::string str, int m)
{
	if (str[0] == '-') {
		isNegative = true;
	}
	else isNegative = false;
	x.resize(str.length());
	for (int i = 0; i < str.length(); i++) {
		x[i] = str[i] - '0';
	}
	this->m = m;
}

Arithmetic::Arithmetic()
{
	this->m = 0;
	this->isNegative = false;
}

//returning remainder - not ready
Arithmetic intdivide(Arithmetic number1, Arithmetic number2)
{
	int n = number1.x.size();
	int t = number2.x.size();
	Arithmetic result, current;
	Arithmetic quotient;
	int x = 0;
	int l = 0;

	quotient.x.resize(n - t);
	for (int j = 0; j < (n - t); j++) quotient.x[j] = 0;
	//cannot divide by zero
	//if (number2.x.size() == 1 && number2.x[0] == 0) 
	for (int i = n - 1; i >= 0; --i) {
		current.shiftRight();
		current.x[0] = number1.x[i];
		current.removeZeros();
		x = 0;
		l = 0;
		while (l <= 10) {
			int m = (l + 10) / 2;

		}
	}
}

std::ostream& operator<<(std::ostream& stream, Arithmetic& number)
{
	if (number.isNegative) stream << '-';
	for (int i = 0; i < number.x.size(); i++) {
		stream << number.x[i];
	}
	return stream;
}

bool operator==(Arithmetic& number1, Arithmetic& number2)
{
	if (number1.isNegative != number2.isNegative) return false;
	if (number1.x.size() != number2.x.size()) return false;
	for (int i = 0; i < number1.x.size(); i++)
		if (number1.x[i] != number2.x[i]) return false;
	return true;
}

//Arithmetic multiply(Arithmetic number1, Arithmetic number2, int module)
//{
//	
//}

Arithmetic intmultiply(Arithmetic number1, Arithmetic number2)
{
	Arithmetic result;
	int n = number1.x.size();
	int t = number2.x.size();
	int size = n + t + 1;
	result.x.resize(size);
	for (int i = 0; i < size; i++) result.x[i] = 0;
	int c = 0;

	if (number1.isNegative && !number2.isNegative) result.isNegative = true;
	if (number2.isNegative && !number1.isNegative) result.isNegative = true;

	for (int i = 0; i < t; i++) {
		c = 0;
		for (int j = 0; j < n; j++) {
			int current = result.x[i + j] + number2.x[i] * number1.x[j] + c;
			result.x[i + j] = current % 10;
			c = (int)current / 10;
		}
		result.x[i + n + 1] = c;
	}
	result.removeZeros();
	return result;
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


