#pragma once
#include"ModArithmetic.h"
#include "MultiplicativeGroupModN.h"

LongModInt pow(const LongModInt& , const LongModInt&);

void eulerCarmichaelTest();
bool isCarmichaelNumber(int n);
int power(int x, int y, int mod);
bool is_prime(int n);
int gcd(int a, int b);
int euler(int n);


