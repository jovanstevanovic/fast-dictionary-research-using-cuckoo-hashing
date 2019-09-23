#include "Hash_Table.h"
#include "BDLHash.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

HashT::HashT(int nn) {
	int s;
	t = new string[n = nn]; br = 0;
	k = new int[n]; br_neusp_pret = 0; br_neusp_pristupa = 0, br_uspes_pristupa = 0;
	cout << "Korak pri razresavanju kolizija? "; cin >> s;
	af = new BDLHash("Bidirekciono linearno adresiranje", s);
	brisi();
}

bool HashT::dodajKljuc(int kljuc, string s) {
	int a = hash(kljuc), i = 0;
	do {
		int j = (*af).dohvAdr(kljuc, a, i, n);
		if (!popunjeno(j) || t[j] == "IZBRISAN") {
			t[j] = s;
			k[j] = kljuc;
			br++;
			br_uspes_pristupa += i + 1;
			return true;
		}
		else {
			if (k[j] == kljuc) return false;
			i++;
		}
	} while (i != n);
	return false;
}

string* HashT::nadjiKljuc(int kljuc, int& i) {
	int a = hash(kljuc); i = 0;
	int j;
	do {
		j = (*af).dohvAdr(kljuc, a, i, n);
		if (k[j] == kljuc && t[j] != "IZBRISAN") {
			return t + j;
		}
		else {
			i++;
		}
	} while (t[j] != "PRAZNO" && i != n);
	br_neusp_pristupa += i;
	br_neusp_pret++;
	return nullptr;
}

bool HashT::izbrisiKljuc(int kljuc) {
	int i = 0;
	string* s = nadjiKljuc(kljuc, i);
	if (s == nullptr || (*s) == "IZBRISAN") return false;
	br_uspes_pristupa -= i + 1;
	*s = "IZBRISAN";
	br--;
	return true;
}

void HashT::brisi() {
	for (int i = 0; i < n; i++) t[i] = "PRAZNO";
	for (int i = 0; i < n; i++) k[i] = -1;
	br = 0;
}

ostream& operator<<(ostream& it, const HashT& ht) {
	for (int i = 0; i < ht.n; i++) it << i << "\t\t" << ht.k[i] << "\t\t" << ht.t[i] << endl;
	return it;
}

int HashT::min() const {
	int min = k[0];
	for (int i = 1; i < n; i++) {
		if (min > k[i] && k[i] != -1) min = k[i];
	}
	return min;
}

int HashT::max() const {
	int max = k[0];
	for (int i = 1; i < n; i++) {
		if (max < k[i]) max = k[i];
	}
	return max;
}
