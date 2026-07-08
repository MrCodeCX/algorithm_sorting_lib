#pragma once
#include "pch.h"

namespace Pointwise
{
	void add_Acumulate(vector<int>& vect);

	void add_Acumulate(vector<long long>& vect);
	
	void add_Scalar(vector<int>& vect, int scalar);

	void add_Scalar(vector<long long>& vect, long long scalar);

	void mul_Scalar(vector<int>& vect, int scalar);

	void mul_Scalar(vector<long long>& vect, long long scalar);

	int get_cif(int num, int pot);

	long long get_cif(long long num, int pot);



	// UTIL
	template<typename T>
	void show(vector<T>& vect) {
		for (int i = 0; i < vect.size(); i++)
		{
			cout << vect[i] << " ";
		}
		cout << endl;
	}

	template<typename T>
	void show(list<T>& lst) {
		for (T& i : lst)
		{
			cout << i << " ";
		}
		cout << endl;
	}

};

