#include "Pointwise.h"

namespace Pointwise {

	void add_Acumulate(vector<int>& vect)
	{
		int n = vect.size();
		for (int i = 1; i < n; i++)
		{
			vect[i] += vect[i - 1];
		}
	}

	void add_Acumulate(vector<long long>& vect) {
		int n = vect.size();
		for (int i = 1; i < n; i++)
		{
			vect[i] += vect[i - 1];
		}
	}

	void add_Scalar(vector<int>& vect, int scalar)
	{
		int n = vect.size();
		for (int i = 0; i < n; i++)
		{
			vect[i] += scalar;
		}
	}

	void add_Scalar(vector<long long>& vect, long long scalar)
	{
		int n = vect.size();
		for (int i = 0; i < n; i++)
		{
			vect[i] += scalar;
		}
	}

	void mul_Scalar(vector<int>& vect, int scalar)
	{
		int n = vect.size();
		for (int i = 0; i < n; i++)
		{
			vect[i] *= scalar;
		}
	}

	void mul_Scalar(vector<long long>& vect, long long scalar)
	{
		int n = vect.size();
		for (int i = 0; i < n; i++)
		{
			vect[i] *= scalar;
		}
	}

	int get_cif(int num, int pot)
	{
		int pow10 = pow(10, pot);
		return ((num / pow10) % 10);
	}

	long long get_cif(long long num, int pot)
	{
		long long pow10 = pow(10, pot);
		return ((num / pow10) % 10);
	}


}
