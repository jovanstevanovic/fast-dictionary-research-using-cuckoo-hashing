#include "Klasa_HashT.h"
#include "Klasa_Univer_Hash.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

HashT::HashT(int nn) {
	t1 = new string[n = nn]; br = 0;
	t2 = new string[n];
	k1 = new int[n]; k2 = new int[n];
	br_neusp_pret = 0; br_neusp_pristupa = 0; br_uspes_pristupa = 0; br_r_hes = 0; br_uspes_pret = 0;
	af = new GUniver(n);
	((GUniver*)af)->generisi_niz_a();
	brisi();
}

bool HashT::pokusaj_dodavanje(int& kljuc, string& s, bool& postoji) {
	int i = 0;
	do {
		int j;
		if (i % 2 == 0) {
			j = (*af).hash(kljuc, 1);
			if (!popunjeno(j) || t1[j] == "IZBRISAN") {
				t1[j] = s;     
				k1[j] = kljuc; br++;
				return true;
			}
			else {
				if (k1[j] == kljuc) { postoji = true;  return false; }
				if (i != 0) {
					int pom = k1[j];
					k1[j] = kljuc;
					kljuc = pom;
					string poms = t1[j];
					t1[j] = s;
					s = poms;
					i++;
				}
				if (i == 0) i++;
			}
		}
		else {
			j = (*af).hash(kljuc, 2);                           
			if (!(popunjeno(j, 2)) || t2[j] == "IZBRISAN") {
				t2[j] = s;
				k2[j] = kljuc; br++;
				return true;
			}
			else {
				if (k2[j] == kljuc) { postoji = true;  return false; }
				int pom = k2[j];
				k2[j] = kljuc;
				kljuc = pom;
				string poms = t2[j];
				t2[j] = s;
				s = poms;
				i++;
			}
		}
	} while (i <= ceil(log2(n)));
	return false;
}

string* HashT::nadjiKljuc(int kljuc, int& i) {
	int j = (*af).hash(kljuc, 1);
	i++;
	if (k1[j] == kljuc) { br_uspes_pret++;  br_uspes_pristupa += 1; return t1 + j; };
	j = (*af).hash(kljuc, 2);
	i++;
	if (k2[j] == kljuc) { br_uspes_pret++;  br_uspes_pristupa += 2; return t2 + j; };
	br_neusp_pristupa += 2;
	br_neusp_pret++;
	return nullptr;
}

bool HashT::izbrisiKljuc(int kljuc) {
	int i = 0;
	string* s = nadjiKljuc(kljuc, i);
	if (s == nullptr) return false;
	*s = "IZBRISAN";
	br--;
	return true;
}

void HashT::brisi() {
	for (int i = 0; i < n; i++) t1[i] = t2[i] = "PRAZNO";
	for (int i = 0; i < n; i++) k1[i] = k2[i] = -1;
	br = 0;
}

ostream& operator<<(ostream& it, const HashT& ht) {
	cout << "\nHES TABELA 1: " << endl;
	for (int i = 0; i < ht.n; i++) it << i << "\t\t" << ht.k1[i] << "\t\t" << ht.t1[i] << endl;
	cout << "\nHES TABELA 2: " << endl;
	for (int i = 0; i < ht.n; i++) it << i << "\t\t" << ht.k2[i] << "\t\t" << ht.t2[i] << endl;
	return it;
}

int HashT::min() const {
	int min = k1[0];
	for (int i = 1; i < n; i++) {
		if (min > k1[i] && k1[i] != -1) min = k1[i];
	}
	return min;
}

int HashT::max() const {
	int max = k1[0];
	for (int i = 1; i < n; i++) {
		if (max < k1[i]) max = k1[i];
	}
	return max;
}

bool HashT::dodajKljuc(int kljuc, string s) { 
	bool postoji = false;
	bool uspeh = pokusaj_dodavanje(kljuc, s, postoji);
	if (uspeh == true) return uspeh;
	if (postoji == true) return false;
	br_r_hes += 2;
	uspeh = rehesiranje(kljuc, s);
	if (uspeh == true) return uspeh;
	else return false;
}

bool HashT::rehesiranje(int kljuc, string s) {
	bool postoji = false;
	int* pom = new int[2 * n + 1];
	string* poms = new string[2 * n + 1];
	for (int i = 0, j = 1; i < n; i++, j++) { pom[j] = k1[i]; poms[j] = t1[i]; }
	for (int i = 0, j = n + 1; i < n; i++, j++) { pom[j] = k2[i]; poms[j] = t2[i]; }
	pom[0] = kljuc; poms[0] = s;
	for (int i = br_r_hes; i < 10'000; i++) {
		brisi();
		postoji = false;
		((GUniver*)af)->generisi_niz_a();
		bool uspeh;
		for (int j = 0; j < 2 * n + 1; j++) {
				if (poms[j] != "PRAZNO") {
					postoji = false;
					int kljuc = pom[j];
					string pms = poms[j];
					uspeh = pokusaj_dodavanje(kljuc, pms, postoji);
					if (uspeh == true || postoji == true) continue;
					else break;
				}
		}
		if (uspeh == false && postoji == false) {
				br_r_hes += 2;
				continue;
		}
		return true;
	}
	delete[] pom;
	delete[] poms;
	return false;
}
