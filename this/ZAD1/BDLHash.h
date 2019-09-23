#ifndef _BDLHash_h_
#define _BDLHash_h_

#include "Addr_Fun.h"
#include <string>
#include <cmath>
using namespace std;

class BDLHash : public Adr_Fun {
public:
	using Adr_Fun::Adr_Fun;
	int dohvAdr(int k, int a, int i, int n) {
		int pom = (int)(pow(-1, i + 1) * korak * ceil((double)i / 2));
		if (a + pom >= 0) return (a + pom) % n;
		else return n + a + pom;
	}
};

#endif
