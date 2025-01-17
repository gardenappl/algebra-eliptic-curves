#pragma once

#include "ModArithmetic.h"
#include <iostream>
#include <vector>
#include <string>

// multiplicative group of integers modulo n - Zn* = {a from integers modulo n | gcd(a, n) = 1}
class MultiplicativeGroupModN {
private:
	LongModInt order;
	std::vector<LongModInt> elements;

public:
	MultiplicativeGroupModN(ModField* f);
	LongModInt getOrder();
	bool isGroupElement(const LongModInt& element);

	friend std::ostream& operator <<(std::ostream& stream, const MultiplicativeGroupModN& group);
};