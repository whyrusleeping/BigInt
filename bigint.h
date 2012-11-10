#ifndef BIGINT_PRIME_H
#define BIGINT_PRIME_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::vector;

class bigint 
{
	public:
		bigint();
		
		static void Init();

		bigint &operator= (const bigint &rhs);
		bigint &operator= (const int &rhs);
		
		bigint &operator+ (const bigint &rhs);
		bigint &operator+ (const int &rhs);

		bigint &operator- (const bigint &rhs);
		bigint &operator- (const int &rhs);

		bigint &operator* (const bigint &rhs);
		bigint &operator* (const int &rhs);

		bigint &operator/ (const bigint &rhs);
		bigint &operator/ (const int &rhs);

		void print();

		static vector<int> primes;
	private:
		static bool initialized;
		vector<int> factors;

		vector<int> factorize(int num);
		vector<int> greatestCommonFactor(vector<int> a, vector<int> b);
};

//vector<int> bigint::primes;
#endif
