#pragma once
#include"ModArithmetic.h"
#include "MultiplicativeGroupModN.h"

struct binary {
	LongModInt order;
	int bit;
};

LongModInt pow(const LongModInt&, const LongModInt&);
std::vector<binary> exponent(LongModInt number, int& breakpoint, int& length);
bool isCoprime(const LongModInt& number1);
LongModInt mont(const LongModInt& number, const LongInt& r);
std::string convert(std::vector<int>x);
LongInt LongModInt_to_LongInt(const LongModInt& x);
LongInt inverse(const LongInt& x, const LongModInt& number);
LongInt modR(const LongInt& x, const LongInt& r);
LongModInt montgomeryMltpl(const LongModInt& number1, const LongModInt& number2, const LongInt& r, const LongInt& k, const LongInt& N);

void eulerCarmichaelTest();
bool isCarmichaelNumber(int n);
int power(int x, int y, int mod);
bool is_prime(int n);
int gcd(int a, int b);
int euler(int n);


