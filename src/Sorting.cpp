#include "Sorting.h"

namespace Sorting {

	// SORTING INTEGER

	vector<int> counting_sort(vector<int>& vect, int max)
	{
		vector<int> vect_counting((max + 1), 0); int n = vect.size();
		vector<int> vect_return(n);
		for (int i = 0; i < n; i++)
		{
			vect_counting[vect[i]]++;
		}
		Pointwise::add_Acumulate(vect_counting);
		for (int i = (n - 1); i >= 0; i--)
		{
			vect_counting[vect[i]]--;
			vect_return[vect_counting[vect[i]]] = vect[i];
		}
		return vect_return;
	}

	vector<int> counting_sort(vector<int>& vect, int max, int min)
	{
		// No es lo más eficiente, pero el aumento de O(n) es lineal
		int n = vect.size(); 
		vector<int> vect_return = vect;
		Pointwise::add_Scalar(vect_return, -min);
		vect_return = counting_sort(vect_return, (max - min));
		Pointwise::add_Scalar(vect_return, min);
		return vect_return;
	}

	vector<long long> counting_sort(vector<long long>& vect, long long max)
	{
		vector<int> vect_counting((max + 1), 0); int n = vect.size();
		vector<long long> vect_return(n);
		for (int i = 0; i < n; i++)
		{
			vect_counting[vect[i]]++;
		}
		Pointwise::add_Acumulate(vect_counting);
		for (int i = (n - 1); i >= 0; i--)
		{
			vect_counting[vect[i]]--;
			vect_return[vect_counting[vect[i]]] = vect[i];
		}
		return vect_return;
	}

	vector<long long> counting_sort(vector<long long>& vect, long long max, long long min)
	{
		// No es lo más eficiente, pero el aumento de O(n) es lineal
		int n = vect.size();
		vector<long long> vect_return = vect;
		Pointwise::add_Scalar(vect_return, -min);
		vect_return = counting_sort(vect_return, (max - min));
		Pointwise::add_Scalar(vect_return, min);
		return vect_return;
	}

	vector<int> radix_sort(vector<int>& vect, int sup10)
	{
		int n = vect.size(); vector<pair<int, int>> vectKeys(n);
		for (int i = 0; i < n; i++)
		{
			vectKeys[i] = pair<int, int>(Pointwise::get_cif(vect[i], 0), vect[i]);
		}
		vectKeys = counting_sort(vectKeys, 10);
		for (int j = 1; j <= sup10; j++)
		{
			for (int i = 0; i < n; i++)
			{
				vectKeys[i].first = Pointwise::get_cif(vectKeys[i].second, j);
			}
			vectKeys = counting_sort(vectKeys, 10);
		}
		vector<int> vect_return(n);
		for (int i = 0; i < n; i++)
		{
			vect_return[i] = vectKeys[i].second;
		}
		return vect_return;
	}

	vector<long long> radix_sort(vector<long long>& vect, int sup10)
	{
		int n = vect.size(); vector<pair<int, long long>> vectKeys(n);
		for (int i = 0; i < n; i++)
		{
			vectKeys[i] = pair<int, long long>(Pointwise::get_cif(vect[i], 0), vect[i]);
		}
		vectKeys = counting_sort(vectKeys, 10);
		for (int j = 1; j <= sup10; j++)
		{
			for (int i = 0; i < n; i++)
			{
				vectKeys[i].first = Pointwise::get_cif(vectKeys[i].second, j);
			}
			vectKeys = counting_sort(vectKeys, 10);
		}
		vector<long long> vect_return(n);
		for (int i = 0; i < n; i++)
		{
			vect_return[i] = vectKeys[i].second;
		}
		return vect_return;
	}


}
