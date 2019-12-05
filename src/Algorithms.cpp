#include <iostream>
#include<vector>
#include<string>
#include <map>
#include"Algorithms.h"
#include "LongInt.h"

using namespace std;


LongInt gcd(const LongInt& num1, const LongInt& num2)
{
	LongInt x, y;
	return LongInt::gcdExtended(num1, num2, x, y);
}


std::vector<FactorizationStruct> naiveFactorization(LongModInt) {
	// TODO
	std::vector<FactorizationStruct> result{};
	return result;
}

std::vector<binary> exponent(LongModInt number,int&breakpoint,int&length) {

	const int bits = 8;
	LongInt mod = number.getField()->mod;
	length = mod.getSize() * bits;
	std::vector<binary>numberbin; numberbin.resize(length);
	LongModInt order("2", number.getField()), degree("1", number.getField());

	for (int i(length - 1); i >= 0; i--) {
		numberbin[i].order = degree;
		degree = degree * order;
		numberbin[i].bit = 0;
	}

	for (int i(length - 1); i > 0; i--) {
		if (numberbin[i].order > numberbin[i - 1].order) {
			breakpoint = i;
			break;
		}
	}

	for (int i(breakpoint); i < length; i++)
		if (numberbin[i].order <= number) {
			numberbin[i].bit++;
			number = number - numberbin[i].order;
		}

	return numberbin;
}


bool isCoprime(const LongModInt& number1)
{
	std::vector<int> mod = number1.getField()->mod.getNumber();

	int length = number1.getField()->mod.getSize(), lastnum = mod[length - 1];

	if (lastnum == 0 || lastnum == 5)
		return false;

	return true;
}

LongModInt mont(const LongModInt& number, const LongInt& r) {

	LongModInt tmpr(r, number.getField());

	return number * tmpr;
}
std::string convert(std::vector<int>x) {

	std::string res_str;

	int size = x.size();
	res_str.resize(size);

	for (int i(0); i < size; i++) {
		res_str[i] = x[i] + '0';
	}

	return res_str;
}

LongInt LongModInt_to_LongInt(const LongModInt&x) {

	int size = x.getNumber().size();

	std::string res_str = convert(x.getNumber());

	LongInt res(res_str);

	return res;
}
LongInt inverse(const LongInt& x,const LongModInt&number) {

	LongModInt temp(x,number.getField());
	temp = ~temp;

	LongInt res = LongModInt_to_LongInt(temp);

	return res;
}
LongInt modR(const LongInt&x, const LongInt&r) {

	std::vector<int> x_vec = x.getNumber();

	int rsize = r.getSize(), xsize = x.getSize();
	std::vector<int> res_vec(x_vec.begin() + (xsize - rsize + 1), x_vec.end());
	std::string res_str = convert(res_vec);
	LongInt res(res_str);

	return res;
}
LongModInt montgomeryMltpl(const LongModInt& number1, const LongModInt& number2, const LongInt& r,const LongInt&k,const LongInt&N) {

	LongInt num1 = LongModInt_to_LongInt(number1), num2 = LongModInt_to_LongInt(number2);
	LongInt x = num1 * num2;
	LongInt s = x * k;
	s = modR(s, r);
	LongInt t = x + s * N;
	LongInt u = t / r;

	return LongModInt(u,number1.getField());
}

LongModInt pow(const LongModInt& number1, const LongModInt& number2) {
	
	LongModInt result(LongInt("1"), number1.getField()), temp = number1;

	if (number1.getField()->mod != number2.getField()->mod)
		throw std::invalid_argument("Moduli must be equal.");

	int breakpoint = 0,explength=0,rlength=number1.getField()->mod.getSize();

	std::vector<binary>number2bin = exponent(number2, breakpoint, explength);

	
	if (!isCoprime(number1)) {
		for (int i(explength - 1); i >= breakpoint; i--) {
			if (number2bin[i].bit) result = result * temp;
			temp = temp * temp;
		}
	}
	else {

		std::string r_str; r_str.resize(rlength + 1);
		for (int i(1); i < rlength + 1; i++) r_str[i] = '0'; r_str[0] = '1';
		LongInt r(r_str);
		LongInt N = number1.getField()->mod;
		LongInt one("1");
		LongInt k = (r * inverse(r, number1) - one)/N;
		LongModInt montres = mont(result,r),monttemp=mont(number1,r);
		for (int i(explength - 1); i >= breakpoint; i--) {
			if (number2bin[i].bit) montres = montgomeryMltpl(montres,monttemp,r,k,N);
			monttemp = montgomeryMltpl(monttemp, monttemp, r, k, N);
		}
		
		LongModInt R = LongModInt(r,number1.getField());
		result = montres * (~R);
	}

	return result;
}


//////////////////////////


LongModInt determineGroupElementOrder(MultiplicativeGroupModN* const group, const LongModInt& groupElement) {
	if(!group->isGroupElement(groupElement))
		throw std::invalid_argument("Element does not belong to group!");

	LongModInt t = group->getOrder();
	LongModInt neutralElement("1", t.getField());
	LongModInt a;

	std::vector<FactorizationStruct> primeFactorization = naiveFactorization(t);
	int factorizationLength = primeFactorization.size();

	for (int i = 0; i < factorizationLength; i++) {
		t = t / pow(primeFactorization[i].factor, primeFactorization[i].power);
		a = pow(groupElement, t);
		while (a != neutralElement) {
			a = pow(a, primeFactorization[i].factor);
			t = t * primeFactorization[i].factor;
		}
	}

	return t;
}



/*!
 * Euler function and Carmichael function
 * @author Мікуш Павло
 */



int euler(int n){ // returns maximum count of simple numbers lesser than n
	int ret = 1;
	for (int i = 2; i * i <= n; ++i)
	{
		int p = 1;
		while (n % i == 0)
		{
			p *= i;
			n /= i;
		}
		p /= i;
		if (p >= 1) ret *= (p * (i - 1));
	}
	return --n ? n * ret : ret;
}

int gcd(int a, int b) // returns greatest common divisor
{
	if (a < b)
		return gcd(b, a);
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

bool is_prime(int n) { // check if number is prime
	if (n <= 1)
		return true;
	if (n == 2)
		return true;
	if (n%2==0)
		return false;
	for (int j = 3; j * j <= n; j+=2)
		if (n % j == 0) return false;

	return true;
}

int power(int x, int y, int mod) { // recursive function that returns special power using mod
	if (y == 0)
		return 1;
	int temp = power(x, y / 2, mod) % mod;
	temp = (temp * temp) % mod;
	if (y % 2 == 1)
		temp = (temp * x) % mod;
	return temp;
}

bool isCarmichaelNumber(int n) { // checks if given number is Charmichael number
	for (int b = 2; b < n; b++) {
		// If "b" is relatively prime to n
		if (gcd(b, n) == 1) {

			// And pow(b, n-1)%n is not 1,
			// return false.
			if (power(b, n - 1, n) != 1){
				return false;
			}
		}
	}
	return true;
}

void eulerCarmichaelTest(){ // test case for above program
	std::cout << "euler(10) = " << euler(10) << std::endl;
	std::cout << "euler(1) = " << euler(1) << std::endl;
	std::cout << "euler(2) = " << euler(2) << std::endl;
	std::cout << "euler(5) = " << euler(5) << std::endl;
	if(isCarmichaelNumber(561) && !is_prime(561)) std::cout << "561 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
	if(isCarmichaelNumber(1105) && !is_prime(1105)) std::cout << "1105 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
	if(isCarmichaelNumber(2000) && !is_prime(2000)) std::cout << "2000 is Charmichael number" << std::endl;
	else std::cout << "Number is not Charmichael" << std::endl;
}



/*!
 * Discrete logarithm: Baby-step giant-step
 * @author Самокрик Владислав
 */


LongInt power(const LongInt& x, const LongInt& y, const LongInt& mod) { // recursive function that returns special power using mod
	if (y == 0)
		return 1;
	LongInt temp = power(x, y / 2, mod) % mod;
	temp = (temp * temp) % mod;
	if (y % 2 == 1)
		temp = (temp * x) % mod;
	return temp;
}


LongInt sqrt(const LongInt& a) {
	LongInt x0 = a, x1 = (a + 1) / 2;
	while (x1 < x0) {
		x0 = x1;
		x1 = (x1 + a / x1) / 2;
	}
	return x0;
}

// Function to calculate k for given a, b, m
LongInt discreteLogarithm(const LongInt& a, const LongInt& b, const LongInt& m) {

	LongInt n = LongInt(sqrt(m) + 1);

	map<LongInt, LongInt> value;

	// Store all values of a^(n*i) of LHS
	for (LongInt i = n; i >= 1; ) {
		i = i - 1;
		value[power(a, i * n, m)] = i;
	}

	for (LongInt j = 0; j < n;)
	{
		// Calculate (a ^ j) * b and check
		// for collision
		LongInt cur = (power(a, j, m) * b) % m;

		// If collision occurs i.e., LHS = RHS
		if (value[cur] != 0)
		{
			LongInt ans = value[cur] * n - j;
			// Check whether ans lies below m or not
			if (ans < m)
				return ans;
		}
		j = j + 1;
	}
	return -1;
}

LongModInt discreteLogarithmBS(const LongModInt& a, const LongModInt& b) {
	LongInt res = discreteLogarithm(a.getNum(), b.getNum(), a.getField()->mod);
	return LongModInt(res, a.getField());

}

// Driver code
int discreteLogBSGSTest()
{
	ModField f(5);
	LongModInt a(2, &f);
	LongModInt b(3, &f);
	cout << discreteLogarithmBS(a, b) << endl;
	return 0;
}
