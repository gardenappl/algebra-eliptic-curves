#include <iostream>
#include<vector>
#include<string>
#include <map>
#include <memory>
#include"Algorithms.h"
#include "LongInt.h"
#include "EllipticCurve.h"

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

/*!
 * Montgomery modular multiplication
 * @author Мазур Дарина, Монтаг Марина
 */



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


/*!
 * Determine the order of an element of multiplicative group mod N.
 * @author Краснопір Тимур
 */


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
 * Discrete logarithm by Pollard
 * @author Fomin Dmitriy
 */


LongInt mod(LongInt x, LongInt y) {
	if (x >= 0) return x % y;
	else if (x < 0) {
		while (x < (-y)) {
			x = x + y;
		}
		return (y - (-x));
	}
}

LongInt inverse(LongInt a, LongInt m)
{
	a = a % m;
	for (int x = 1; x < m; x++)
		if ((a*x) % m == 1)
			return x;
} 

vector<LongInt> f(vector<LongInt> xab, LongInt g, LongInt t, LongInt p) {
	LongInt x = xab[0];
	LongInt a = xab[1];
	LongInt b = xab[2];
	if (x < p / 3)
		return { (t*x) % p, (a + 1) % (p - 1), b };
	if (p * 2 / 3 < x) return { (g*x) % p, a, (b + 1) % (p - 1) };
	return { (x*x) % p, (a * 2) % (p - 1), (b * 2) % (p - 1) };
}

LongInt dlog(LongInt g, LongInt t, LongInt p) {
	// l such that g**l == t (mod p), with p prime
	// algorithm due to Crandall/Pomerance "Prime Numbers" sec 5.2.2
	LongInt i = 1;
	vector<LongInt> x_i = { 1,0,0 };
	vector<LongInt> x_2i = f(x_i, g, t, p);
	while (x_i[0] != x_2i[0]) {
		//cout << i << " " << x_i[0] << " " << x_i[1] << " " << x_i[2]
		//	<< " " << x_2i[0] << " " << x_2i[1] << " " << x_2i[2] << endl;
		i = i + 1;
		x_i = f(x_i, g, t, p);
		x_2i = f(x_2i, g, t, p);
		x_2i = f(x_2i, g, t, p);
	}
	//cout << i << " " << x_i[0] << " " << x_i[1] << " " << x_i[2]
	//	<< " " << x_2i[0] << " " << x_2i[1] << " " << x_2i[2] << endl;
	LongInt d = gcd(x_i[1] - x_2i[1], p - 1);
	if (d == 1) return mod((mod((x_2i[2] - x_i[2]), (p - 1)) * inverse(mod((x_i[1] - x_2i[1]), (p - 1)), p - 1)), (p - 1));
	int m = 0;
	LongInt l = mod((mod((x_2i[2] - x_i[2]), ((p - 1) / d)) * inverse(mod((x_i[1] - x_2i[1]), ((p - 1) / d)), (p - 1) / d)), ((p - 1) / d));
	while (m <= d) {
		//cout << m << " " << l << endl;
		if (power(g, l, p) == t) return l;
		m++;
		l = mod((l + ((p - 1) / d)), (p - 1));
	}
	return -1;
}

LongModInt discreteLog_pollard(LongModInt g, LongModInt t) {
	LongInt res = dlog(g.getNum(), t.getNum(), g.getField()->mod);
	return LongModInt(res, g.getField());
}

void pollardDiscreteLogTest() {
	ModField f1(383);
	LongModInt a1(2, &f1);
	LongModInt b1(228, &f1);
	cout << "log(2,228) = x mod 383 --> x = 110" << endl << "Checking: ";
	cout << (discreteLog_pollard(a1, b1) == LongModInt(110, &f1)) << " - true " << endl; // log(2,228) = 110 mod 383

	cout << "=============" << endl;
	ModField f2(1019);
	LongModInt a2(2, &f2);
	LongModInt b2(5, &f2);
	cout << "log(2,5) = x mod 1019 --> x = 10" << endl << "Checking: ";
	cout << (discreteLog_pollard(a2, b2) == LongModInt(10, &f2)) << " - true " << endl; // log(2,5) = 10 mod 1019
	cout << "=============" << endl;

	ModField f3(997);
	LongModInt a3(83, &f3);
	LongModInt b3(555, &f3);
	cout << "log(83,555) = x mod 997 --> x = 129" << endl << "Checking: ";
	cout << (discreteLog_pollard(a3, b3) == LongModInt(129, &f3)) << " - true " << endl; // log(83,555) = 129 mod 997
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



/*!
 * Determine order of a point on elliptic curve.
 * @author Пилипенко Павло
 */


int order(const EllipticCurve& curve, const Point& p) {
	int k = 1;
	// текущая точка = сумма k точек P (или k * P)
	// (изначально = P, т.к. k = 1)
	Point current = p;
	// пока текущая точка не ушла в бесконечность
	while (!current.isInfinite()) {
		// добавляем к ней точку P
		current = curve.add(current, p);
		k++;
	}
	// точка ушла в бесконечность,
	// возвращаем сколько раз мы её добавили
	return k;
}

int pointOrderTest() {

	cout << "elliptic curve E(Fp): ";
	cout << "y^2 = x^3 + Ax + B, p prime" << endl;

	string p;
	cout << "enter p: ";
	cin >> p;

	string a;
	cout << "enter A: ";
	cin >> a;

	cout << endl;
	cout << "point P(x, y)" << endl;

	string x;
	cout << "enter x: ";
	cin >> x;

	string y;
	cout << "enter y: ";
	cin >> y;

	// переводим строки в объекты чисел
	unique_ptr<ModField> field(new ModField(p));
	LongModInt ma(a, field.get());
	LongModInt mx(x, field.get());
	LongModInt my(y, field.get());

	// находим такое B, при котором точка будет лежать на кривой
	// B = y^2 - x^3 - Ax
	LongModInt mb = my * my - mx * mx * mx - ma * mx;

	EllipticCurve curve(ma.getNum(), mb.getNum(), field.get());
	Point P(mx, my);

	// выводим B
	cout << endl;
	cout << "B = " << mb << endl;

	// выводим порядок точки P на кривой curve
	cout << endl;
	cout << "ord(P) = " << order(curve, P) << endl;

	return 0;
}

#include <iostream>
#include <cmath>
#include "ModArithmetic.h"
#include "EllipticCurve.h"
#include "Algorithms.h"
#include "MultiplicativeGroupModN.h"

using namespace std;

/*!
 * Get generators of a group.
 * @author Шеремет Іван
 */


vector<LongInt> get_generator(LongInt n, vector<LongInt> prime_factorization) {
	vector<LongInt> res;//Змінна для результату
	LongInt one("1");//Змінна константа 1
	LongInt i("0");//Змінна для циклу

	ModField f(n);
	for (bool flag = true; i < n; i = i + one)//Поки i<n
	{
		for (size_t j = 0; j < prime_factorization.size(); j++)//Перебираемо усі прості дільники
			if (pow(LongModInt(i, &f), LongModInt(n / prime_factorization[j], &f)).getNum() == one)flag = false;//Якщо і^(n/p)==1 то і не генератор
		if (flag)res.push_back(i);//Якщо і генератор то і потрапить у результат
		flag = true;
	}
	return res;
}


void getGeneratorTest()
{
	LongInt n("11");
	vector<LongInt> prime_factorization;
	prime_factorization.push_back(n);
	for (auto generator : get_generator(n, prime_factorization))cout << generator << ' ';
}

/*!
 * Find square root in modular arithmetic
 * @author Іоффе Андрій
 */

LongInt mod_pow(const LongInt& a, const LongInt& b,
                const LongInt& p) {
	ModField field(p);
	LongModInt ma(a, &field);
	LongModInt mb(b, &field);
	return pow(ma, mb).getNum();
}

LongInt legendre(const LongInt& a, const LongInt& p) {
	LongInt ret = mod_pow(a, (p - 1) / 2, p);
	if (ret == p - 1) {
		return LongInt(-1);
	} else {
		return ret;
	}
}

LongInt mod_sqrt(const LongInt& a, const LongInt& p) {
	ModField field(4);
	// field by which we will calculate some modules

	// check value of legendre
	// by algorithm
	LongInt ls = legendre(a, p);
	if (ls != 1) {
		if (ls == -1) {
			cout << endl;
			cout << "a doesnt have a square root modulo p";
			cout << endl;
		}
		return 0;
	} else if (a == 0) {
		return 0;
	} else if (p == 2) {
		return p;
	} else if (LongModInt(p, &field).getNum() == 3) {
		// if p % 4 = 3 --  by algorithm
		return mod_pow(a, (p + 1) / 4, p);
	}

	// by algorithm
	LongInt b = 2;
	while (legendre(b, p) != -1) {
		b = b + 1;
	}

	// by algorithm
	LongInt t = p - 1;
	// by algorithm
	LongInt s = 0;

	field = ModField(2);
	// by algorithm
	while (LongModInt(t, &field).getNum() == 0) {
		t = t / 2;
		s = s + 1;
	}

	// renew field
	field = ModField(p);

	// by algorithm
	LongModInt a1 = ~LongModInt(a, &field);
	// by algorithm
	LongModInt c(mod_pow(b, t, p), &field);
	// by algorithm
	LongModInt r(mod_pow(a, (t + 1) / 2, p), &field);

	// border  of for
	LongInt u = s - 1;
	for (LongInt i = 1; i <= u; i = i + 1) {
		// transfering long int to regular int
		// (sure that it fits in)
		int rm = (s - i).getNumber()[0];
		// по алгоритму
		LongModInt d(
				mod_pow(
						LongModInt(r * r * a1).getNum(),
						// == 2^(rm - 1) == 2^(s - i - 1)
						1 << (rm - 1),
						p
				),
				&field
		);

		if (d == LongModInt(-1, &field)) {
			r = r * c;
		}

		c = c * c;
	}

	return r.getNum();
}

void sqrtTest() {
	cout << "hello world" << endl;

	string sn;
	cout << "enter number: ";
	cin >> sn;

	string sp;
	cout << "enter p: "; // enter p for mod_sqrt(n,p)
	cin >> sp;

	LongInt n = sn; // number
	LongInt p = sp; // mod

	cout << endl;
	cout << "sqrt: " << mod_sqrt(n, p) << endl;
}
