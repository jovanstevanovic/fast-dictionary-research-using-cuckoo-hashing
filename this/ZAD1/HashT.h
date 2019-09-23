#ifndef _Hash_Table_h_
#define _Hash_Table_h_

#include "Addr_Fun.h"
#include "BDLHash.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class HashT {
	Adr_Fun* af;
	string* t;
	int* k;
	int br, n; int br_neusp_pret, br_neusp_pristupa, br_uspes_pristupa;
public:
	HashT() : t(nullptr), k(nullptr), br(0), n(0), br_neusp_pret(0), br_neusp_pristupa(0), br_uspes_pristupa(0) { }
	explicit HashT(int nn);
	HashT(const HashT& ht) = delete;
	HashT(HashT&& ht) = delete;
	HashT& operator= (const HashT& ht) = delete;
	HashT& operator= (HashT&& ht) = delete;
	~HashT() { delete[] t; delete[] k, k = nullptr; t = nullptr; br = n = 0; }
	int hash(int kljuc) const { return kljuc % n; }
	bool prazna() { return br == 0; }
	bool puna() { return br == n; }
	bool popunjeno(int a) { return t[a] != "PRAZNO"; }
	string* nadjiKljuc(int kljuc, int& i);
	bool dodajKljuc(int kljuc, string s);
	bool izbrisiKljuc(int kljuc);
	double prosecan_br_uspesno() const {
		if (brKljuceva() == 0) return 0;
		return (double)br_uspes_pristupa / (double)brKljuceva(); 
	}
	double prosecan_br_neuspesno() const {
		if (br_neusp_pret == 0) return 0;
		return (double)br_neusp_pristupa / (double)br_neusp_pret; 
	}
	double prosecan_br_neuspesno_procena() const { return 1 / (1 - popT()); }
	int min() const;
	int max() const;
	void resetuj_statistiku() { br_neusp_pret = br_neusp_pristupa = 0; }
	void brisi();
	int brKljuceva() const { return br; }
	int velT() const { return n; }
	friend ostream& operator<<(ostream& it, const HashT& ht);
	double popT() const { return (double) br / (double) n; }
};

#endif
