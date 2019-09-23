#include "Klasa_HashT.h"
#include "Klasa_Addr_Fun.h"
#include "Klasa_Univer_Hash.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	HashT* ht = nullptr; srand((unsigned int)time(NULL));
	bool kraj = false; int izbor;
	while (!kraj) {
		cout << "\n----------------------------------------\n"
			<< "                HES TABELA             "
			<< "\n----------------------------------------\n" << endl;
		cout << "1. Stvaranje prazne hesh tabele\n"
			<< "2. Umetanje u hes tabelu citanjem sa std ulaza\n"
			<< "3. Umetanje u hes tabelu citanjem iz datoteke\n"
			<< "4. Pretrazivanje na zadati kljuc\n"
			<< "5. Pretrazivanje na generisani skup kljuceva\n"
			<< "6. Brisanje na zadati kljuc\n"
			<< "7. Prosecan broj pristupa pri uspesnom trazenju\n"
			<< "8. Prosecan broj pristupa pri neuspesnom trazenju\n"
			<< "9. Prosecan broj pristupa pri neuspesnom trazenju uz procenu\n"
			<< "10. Resetovanje statistike\n"
			<< "11. Praznjenje cele hes tabele\n"
			<< "12. Broj umetnutih kljuceva\n"
			<< "13. Velicina tabele\n"
			<< "14. Ispis tabele\n"
			<< "15. Popunjenost tabele\n"
			<< "16. Kraj rada!\n";
		cout << "Izbor? "; cin >> izbor;
		switch (izbor) {
		case 1: {
			int m;
			cout << "\nKapacitet? "; cin >> m;
			ht = new HashT(m);
			cout << "Hes tabela je uspesno formirana!" << endl;
			break;
		}
		case 2: {
			string s;
			int kljuc;
			bool uspeh;
			cout << "\nNiska koju zelite da umetnete? "; cin >> s;
			cout << "Kljuc niske koju zelite da umetnete? "; cin >> kljuc;
			uspeh = ht->dodajKljuc(kljuc, s);
			if (uspeh == true) cout << "Kljuc " << kljuc << " i niska \"" << s << "\" su uspesno dodati!" << endl;
			else cout << "Kljuc " << kljuc << " vec postoji, tabela je puna ili je iscrpljena klasa hes funkcija!" << endl;
			break;
		}
		case 3: {
			ifstream dat;
			int kljuc; int i = 0;
			string s;
			dat.open("10K.txt");
			if (!dat.is_open()) {
				cout << "Ucitavanje datoteke nije uspelo!" << endl;
				break;
			}
			cout << endl;
			while (dat >> s >> kljuc) {
				i++;
				bool uspeh;
				uspeh = ht->dodajKljuc(kljuc, s);
				if (uspeh == true) cout << "Kljuc " << kljuc << " i niska \"" << s << "\" su uspesno dodati!" << endl;
				else cout << "Kljuc " << kljuc << " vec postoji, tabela je puna ili je iscrpljena klasa hes funkcija!" << endl;
			}
			cout << "Hes tabela je uspesno formirana!" << endl;
			break;
		}
		case 4: {
			int kljuc; int i = 0;
			cout << "\nKljuc na koji se vrsi pretrazivanje? "; cin >> kljuc;
			string* s = ht->nadjiKljuc(kljuc, i);
			if (s != nullptr && (*s) != "IZBRISAN") cout << "Kljuc " << kljuc << " i niska \"" << *s << "\" su pronadjeni!" << endl;
			else cout << "Kljuc " << kljuc << " ne postoji!" << endl;
			break;
		}
		case 5: {
			int br, kljuc, j = 0;
			int min = ht->min(), max = ht->max();
			ht->resetuj_statistiku();
			cout << "\nKoliko kljuceva zelite da izgenerisete? "; cin >> br;
			for (int i = 0; i < br; i++) {
				kljuc = (int)((rand() / (double)(RAND_MAX + 1.)) * (max - min) + min);
				string* s = ht->nadjiKljuc(kljuc, j);
				if (s != nullptr) cout << "Kljuc " << kljuc << " i niska \"" << *s << "\" su pronadjeni!" << endl;
				else cout << "Kljuc " << kljuc << " ne postoji!" << endl;
			}
			cout << "\nProsecan broj pristupa pri uspesnom trazenju je " << ht->prosecan_br_uspesno() << '!';
			cout << "\nProsecan broj pristupa pri neuspesnom trazenju je " << ht->prosecan_br_neuspesno() << '!';
			cout << "\nProsecan broj pristupa pri neuspesnom trazenju uz procenu je " << ht->prosecan_br_neuspesno_procena() << '!';
			break;
		}
		case 6: {
			int kljuc;
			bool uspeh;
			cout << "\nKljuc za brisanje? "; cin >> kljuc;
			uspeh = ht->izbrisiKljuc(kljuc);
			if (uspeh == true) cout << "Kljuc " << kljuc << " je uspesno obrisan!" << endl;
			else cout << "Kljuc " << kljuc << " nije pronadjen!" << endl;
			break;
		}
		case 7:
			cout << "\nProsecan broj pristupa pri uspesnom trazenju je " << ht->prosecan_br_uspesno() << '!' << endl;
			break;
		case 8:
			cout << "\nProsecan broj pristupa pri neuspesnom trazenju je " << ht->prosecan_br_neuspesno() << '!' << endl;
			break;
		case 9:
			cout << "\nProsecan broj pristupa pri neuspesnom trazenju uz procenu je " << ht->prosecan_br_neuspesno_procena() << '!' << endl;
			break;
		case 10:
			ht->resetuj_statistiku();
			cout << "\nStatistika je resetovana!" << endl;
			break;
		case 11:
			ht->brisi();
			cout << "\n**** Tabela je ispraznjena! ****" << endl;
			break;
		case 12:
			cout << "\nBroj umetnutih kljuceva je " << ht->brKljuceva() << '!' << endl;
			break;
		case 13:
			cout << "\nVelicina tabele je " << ht->velT() << '!' << endl;
			break;
		case 14:
			cout << *ht << endl;
			break;
		case 15:
			cout << "\nPopunjenost tabele je " << ht->popT() << '!' << endl;
			break;
		case 16:
			cout << "\n**** Izabrana opicija za kraj rada! ****\n";
			kraj = true;
			break;
		default:
			cout << "\n**** Nekorektan unos! Pokusajte ponovo! ****\n";
			break;
		}
	}
}
