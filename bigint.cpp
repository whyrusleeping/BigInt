#include "bigint.h"

bigint::bigint()
{
	factors.resize(256);
}

void bigint::Init()
{
	primes.resize(256);
	int primecount = 0;
	int num = 2;
	while(primecount < 256)
	{
		int i = 2;
		for(; i < sqrt(num) + 1; i++)
		{
			if(!(num % i))
				break;
		}
		if(i > sqrt(num))
			primes[primecount++] = num;
		num++;
	}
}

vector<int> bigint::factorize(int num)
{
	vector<int> tfact(primes.size());
	for(int i = 0; i < primes.size(); i++)
	{
		while(num % primes[i] == 0)
		{
			num /= primes[i];
			tfact[i]++;
		}
	}
	return tfact;
}

vector<int> bigint::greatestCommonFactor(vector<int> a, vector<int> b)
{
	vector<int> gcf(a.size());
	for(int i = 0; i < a.size(); i++)
	{
		gcf[i] = a[i] > b[i] ? b[i] : a[i];
	}
	return gcf;
}

bigint &bigint::operator= (const int &rhs)
{
	factors = factorize(rhs);
	return *this;
}

bigint &bigint::operator= (const bigint &rhs)
{
	factors = rhs.factors;
	return *this;
}

bigint &bigint::operator* (const bigint &rhs)
{
	if(rhs.factors.size() > factors.size())
		factors.resize(rhs.factors.size());

	for(int i = 0; i < factors.size(); i++)
		factors[i] += rhs.factors[i];
	return *this;
}

bigint &bigint::operator* (const int &rhs)
{
	vector<int> rhfactors = factorize(rhs);
	for(int i = 0; i < factors.size(); i++)
		factors[i] += rhfactors[i];
	return *this;
}

bigint &bigint::operator/ (const int &rhs)
{
	vector<int> rhfactors = factorize(rhs);
	for(int i = 0; i < factors.size(); i++)
		factors[i] -= rhfactors[i];
	return *this;
}

bigint &bigint::operator/ (const bigint &rhs)
{
	for(int i = 0; i < factors.size(); i++)
		factors[i] -= rhs.factors[i];
	return *this;
}

bigint &bigint::operator+ (const int &rhs)
{
	vector<int> rhfactors = factorize(rhs);
	vector<int> gcf = greatestCommonFactor(factors, rhfactors);
	vector<int> leftoverTop(factors.size());
	vector<int> leftoverBot(factors.size());

	for(int i = 0; i < factors.size(); i++)
		leftoverTop[i] = abs(factors[i] - gcf[i]);

	for(int i = 0; i < factors.size(); i++)
		leftoverBot[i] = abs(rhfactors[i] - gcf[i]);

	long long topSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverTop[i] != 0)
		{
			topSum += pow(primes[i], leftoverTop[i]);
		}
	}

	long long botSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverBot[i] != 0)
		{
			botSum += pow(primes[i], leftoverBot[i]);
		}
	}

	//Here we have the possibility of overflowing the integer type
	leftoverTop = factorize(topSum + botSum);
	for(int i = 0; i < factors.size(); i++)
	{
		factors[i] = leftoverTop[i] + gcf[i];
	}
	return *this;
}

bigint &bigint::operator+ (const bigint &rhs)
{
	vector<int> gcf = greatestCommonFactor(factors, rhs.factors);
	vector<int> leftoverTop(factors.size());
	vector<int> leftoverBot(factors.size());

	for(int i = 0; i < factors.size(); i++)
		leftoverTop[i] = abs(factors[i] - gcf[i]);

	for(int i = 0; i < factors.size(); i++)
		leftoverBot[i] = abs(rhs.factors[i] - gcf[i]);

	long long topSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverTop[i] != 0)
		{
			topSum += pow(primes[i], leftoverTop[i]);
		}
	}

	long long botSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverBot[i] != 0)
		{
			botSum += pow(primes[i], leftoverBot[i]);
		}
	}

	//Here we have the possibility of overflowing the integer type
	leftoverTop = factorize(topSum + botSum);
	for(int i = 0; i < factors.size(); i++)
	{
		factors[i] = leftoverTop[i] + gcf[i];
	}
	return *this;
}

bigint &bigint::operator- (const int &rhs)
{
	vector<int> rhfactors = factorize(rhs);
	vector<int> gcf = greatestCommonFactor(factors, rhfactors);
	vector<int> leftoverTop(factors.size());
	vector<int> leftoverBot(factors.size());

	for(int i = 0; i < factors.size(); i++)
		leftoverTop[i] = abs(factors[i] - gcf[i]);

	for(int i = 0; i < factors.size(); i++)
		leftoverBot[i] = abs(rhfactors[i] - gcf[i]);

	long long topSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverTop[i] != 0)
		{
			topSum += pow(primes[i], leftoverTop[i]);
		}
	}

	long long botSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverBot[i] != 0)
		{
			botSum += pow(primes[i], leftoverBot[i]);
		}
	}

	leftoverTop = factorize(topSum - botSum);
	for(int i = 0; i < factors.size(); i++)
	{
		factors[i] = leftoverTop[i] + gcf[i];
	}
	return *this;
}

bigint &bigint::operator- (const bigint &rhs)
{
	vector<int> gcf = greatestCommonFactor(factors, rhs.factors);
	vector<int> leftoverTop(factors.size());
	vector<int> leftoverBot(factors.size());

	for(int i = 0; i < factors.size(); i++)
		leftoverTop[i] = abs(factors[i] - gcf[i]);

	for(int i = 0; i < factors.size(); i++)
		leftoverBot[i] = abs(rhs.factors[i] - gcf[i]);

	long long topSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverTop[i] != 0)
		{
			topSum += pow(primes[i], leftoverTop[i]);
		}
	}

	long long botSum = 0;
	for(int i = 0; i < factors.size(); i++)
	{
		if(leftoverTop[i] != 0)
		{
			botSum += pow(primes[i], leftoverBot[i]);
		}
	}

	leftoverTop = factorize(topSum - botSum);
	for(int i = 0; i < factors.size(); i++)
	{
		factors[i] = leftoverTop[i] + gcf[i];
	}
	return *this;
}

void bigint::print()
{
	for(int i = 0; i < factors.size(); i++)
	{
		if(factors[i] != 0)
		{
			cout << primes[i] << "^" << factors[i] << "\n";
		}
	}
}
