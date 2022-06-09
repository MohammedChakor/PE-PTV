//TSP.cpp

#include "Tsp.h"

void TSP::runTSP() {
	
	cout << "TSP"<< endl;
	Tour bestTour = tour;
	Tour search;
	PiecewiseLinearFunction ibaraki1;
	PiecewiseLinearFunction ibaraki2;
	int k = 0;
	int tabu = 0;
	int size = tour.getSize() - 1;
	cout << size << endl;
	int j = size - 1;
	int i = 0;
	
	while (j > 0) {	
		while (k < size) {
			i++;
			tour = bestTour;
			search = tour;

			search.switchCustomers(tabu + k, tabu + k + j, 1);
				
			ibaraki1 = tour.ibarakiFunction(size);
			ibaraki2 = search.ibarakiFunction(size);
				
			if (search.evaluate(ibaraki2) < tour.evaluate(ibaraki1)) {
				bestTour = search;
				k = 0;
				}
			else {
				k += 1;
				}
		}
		j--;
	}

	tour = bestTour;
	cout << "Tabu: " << tabu << endl;
	cout << "Number of switch :" << i << endl;
}
