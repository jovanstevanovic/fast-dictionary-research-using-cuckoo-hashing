#ifndef _Klasa_Univer_Hash_h_
#define _Klasa_Univer_Hash_h_

#include "Klasa_Addr_Fun.h"

class GUniver : public Adr_Fun {
	int* a1, *a2;
	int r, n;
public:
	GUniver(int n) : a1(nullptr), a2(nullptr), r(10), n(n) { }
	GUniver(const GUniver& gu) = delete;
	GUniver(GUniver&& gu) = delete;
	GUniver& operator= (const GUniver& gu) = delete;
	GUniver& operator= (GUniver&& gu) = delete;
	~GUniver() { delete[] a1; delete[] a2; a1 = a2 = nullptr; }
	void generisi_niz_a();
	int hash(int kljuc, int t);
};

#endif
