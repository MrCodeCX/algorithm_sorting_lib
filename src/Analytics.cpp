#include "Analytics.h"

namespace Analytics {

	int binary_search(vector<int>& vect, int look)
	{
		int start = 0; int end = vect.size() - 1;
		int pot = (1 + start + end) / 2;
		// La actualizacion tira hacia arriba
		while (vect[pot] != look) {
			if (vect[pot] < look) start = pot;
			else if (vect[pot] > look) end = pot;
			pot = (start + end) / 2;
		}
		// Encontrar el minimo pot = look
		// La actualizacion tira hacia abajo
		end = pot; int newpot = (start + end) / 2; 
		while (end != newpot) {
			if (vect[newpot] == look) end = newpot;
			else start = (newpot + 1);
			newpot = (start + end) / 2;
		}
		return newpot;
	}

}