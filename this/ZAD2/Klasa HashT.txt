#ifndef _Hash_Table_h_
#define _Hash_Table_h_

#include "Klasa_Addr_Fun.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class HashT {
	Adr_Fun* af;
	string* t1, *t2;
	int* k1, *k2;
	int br, n; int br_neusp_pret, br_neusp_pristupa, br_uspes_pristupa, br_uspes_pret;
	int br_r_hes;
public:
	HashT() : t1(nullptr), k1(nullptr), t2(nullptr), k2(nullptr),
		br(0), n(0), br_neusp_pret(0), br_neusp_pristupa(0), br_uspes_pristupa(0), br_r_hes(0), br_uspes_pret(0) { }
	explicit HashT(int nn);
	HashT(const HashT& ht) = delete;
	HashT(HashT&& ht) = delete;
	HashT& operator= (const HashT& ht) = delete;
	HashT& operator= (HashT&& ht) = delete;
	~HashT() { 
		delete[] t1; delete[] k1, k1 = nullptr; t1 = nullptr; 
		delete[] t2; delete[] k2, k2 = nullptr; t2 = nullptr;
		br = n = 0; 
	}
	bool prazna() { return br == 0; }
	bool puna() { return br == n; }
	bool popunjeno(int a, int t = 1) { 
		if (t == 1)
			return t1[a] != "PRAZNO";
		else
			return t2[a] != "PRAZNO";
	}
	string* nadjiKljuc(int kljuc, int& i);
	bool dodajKljuc(int kljuc, string s);
	bool pokusaj_dodavanje(int& kljuc, string& s, bool& postoji);
	bool rehesiranje(int kljuc, string s);
	bool izbrisiKljuc(int kljuc);
	double prosecan_br_uspesno() const {
		if (br_uspes_pret == 0) return 0;
		return (double)br_uspes_pristupa / (double)br_uspes_pret;
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
	double popT() const { return (double)br / ((double)n * 2); }
};

#endif
