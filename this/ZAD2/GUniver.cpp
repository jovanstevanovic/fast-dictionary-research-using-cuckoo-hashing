#include "Klasa_Univer_Hash.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void GUniver::generisi_niz_a() {
	a1 = new int[r];
	a2 = new int[r];
	for (int i = 0; i < r; i++) {
		a1[i] = (int)((rand() / (double)(RAND_MAX + 1.)) * (n - 1));
		a2[i] = (int)((rand() / (double)(RAND_MAX + 1.)) * (n - 1));
	}
}

int GUniver::hash(int kljuc, int t) {
	int adr = 0;
	for (int i = 0; i < r; i++) {
		int odsecak = kljuc % 10;
		kljuc /= 10;
		if (t == 1)
		   adr += odsecak * a1[i];
		else
		   adr += odsecak * a2[i];
	}
	return adr % n;
}
