#ifndef _Adr_Fun_h_
#define _Adr_Fun_h_

#include <string>
using namespace std;

class Adr_Fun {
protected:
	string tip;
	int korak;
public:
	Adr_Fun(string tip = "", int korak = 1) : tip(tip), korak(korak) { }
	string dohvTip() const { return tip; }
	virtual int hash(int kljuc, int t) = 0;
};

#endif
