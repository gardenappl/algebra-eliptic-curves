#pragma once
#include"ModArithmetic.h"
#include "MultiplicativeGroupModN.h"
#include "EllipticCurve.h"

struct FactorizationStruct {
	LongModInt factor;
	LongModInt power;
};

struct binary {
	LongModInt order;
	int bit;
};


LongInt gcd(const LongInt& a, const LongInt& b);

LongModInt pow(const LongModInt&, const LongModInt&);
std::vector<binary> exponent(LongModInt number, int& breakpoint, int& length);
bool isCoprime(const LongModInt& number1);
LongModInt mont(const LongModInt& number, const LongInt& r);
std::string convert(std::vector<int>x);
LongInt LongModInt_to_LongInt(const LongModInt& x);
LongInt inverse(const LongInt& x, const LongModInt& number);
LongInt modR(const LongInt& x, const LongInt& r);
LongModInt montgomeryMltpl(const LongModInt& number1, const LongModInt& number2, const LongInt& r, const LongInt& k, const LongInt& N);

LongModInt determineGroupElementOrder(MultiplicativeGroupModN* const group, const LongModInt& groupElement);

int gcd(int a, int b);
void eulerCarmichaelTest();
bool isCarmichaelNumber(int n);
int euler(int n);

LongModInt discreteLogarithmBS(const LongModInt& a, const LongModInt& b);
int discreteLogBSGSTest();

int order(const EllipticCurve& curve, const Point& p);
int pointOrderTest();

vector<LongInt> get_generator(LongInt n, vector<LongInt> prime_factorization);
void getGeneratorTest();

LongInt mod_sqrt(const LongInt& a, const LongInt& p);
void sqrtTest();

std::vector<FactorizationStruct> naiveFactorization(LongModInt a);