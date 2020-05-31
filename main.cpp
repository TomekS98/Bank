#include "funkcje.h"
#include "struktury.h"
#include <iostream>

int main(int argc, char * argv[]) {	// Uaktualnic argc *argv[] dla ponizszych zmian 
	const char * UPDATE11 ="nazwa.txt";
	int rozkaz = 1;
	dane* pHead = NULL;
	transakcja* pHead2 = NULL;
	std::cout << "-fin<nazwa> - wczytywanie danych z pliku o danej nazwie" << std::endl;																			// jest OK
	std::cout << "-wy<id><kwota> - wyplata kwoty z konta" << std::endl;																								// jest OK
	std::cout << "-we<id><kwota> - wplata kwoty na konto" << std::endl;																								// jest OK
	std::cout << "-wyciag<id>(<s><m><g><dz><mies><r>)x2 - wyciag z konta za okreslony okres" << std::endl;															// jest OK
	std::cout << "-undo <nrkonta><dzien><miesiac><rok><kwota> -cofniecie transakcji" << std::endl;																	// jest OK
	std::cout << "-wywe <adr><odb><kwota>- wplata dowolnej kwoty na konto innego uzytkownika" << std::endl;															// jest OK
	std::cout << "-rT <id/nazw><nazwa>(<s><m><g><dz><mies><r>)x2 - zapisanie raportu wykonanych w banku operacji w tym okresie" << std::endl;						// jest OK
	std::cout << "-rD <nazwa> - zapisanie raportu u¿ytkownikow, ktorzy maja debet na koncie" << std::endl;															// Jest OK
	while (rozkaz+1 < argc) {
		std::string s = argv[rozkaz];
		if (s == "-fin") {
			UPDATE11 = argv[rozkaz + 1];
			odczytZPliku(pHead, UPDATE11); // odczytZPliku(pHead,argv[rozkaz+1]);
			rozkaz++;
			rozkaz++;
		}
		else if (s == "-wy" && rozkaz + 2 < argc) {
			std::string s2 = argv[rozkaz + 1];
			std::string s3 = argv[rozkaz + 2];
			int kwota = stoi(s3);
			int id = stoi(s2);
			wyplata(pHead, id, kwota);
			rozkaz++;
			rozkaz++;
			rozkaz++;
		}
		else if (s == "-we" && rozkaz + 2 < argc) {
			std::string s2 = argv[rozkaz + 1];
			std::string s3 = argv[rozkaz + 2];
			int id = stoi(s2);
			int kwota = stoi(s3);
			wplata(pHead, id, kwota);
			rozkaz++;
			rozkaz++;
			rozkaz++;
		}
		else if (s == "-wyciag" && rozkaz+13 <argc) {
			std::string s1 = argv[rozkaz + 1]; int id = stoi(s1);
			std::string s2 = argv[rozkaz + 2]; int s = stoi(s2);
			std::string s3 = argv[rozkaz + 3]; int m = stoi(s3);
			std::string s4 = argv[rozkaz + 4]; int g = stoi(s4);
			std::string s5 = argv[rozkaz + 5]; int dz = stoi(s5);
			std::string s6 = argv[rozkaz + 6]; int mm = stoi(s6);
			std::string s7 = argv[rozkaz + 7]; int r = stoi(s7);
			std::string s8 = argv[rozkaz + 8]; int sek2 = stoi(s8);
			std::string s9 = argv[rozkaz + 9]; int m2 = stoi(s9);
			std::string s10 = argv[rozkaz + 10]; int g2 = stoi(s10);
			std::string s11 = argv[rozkaz + 11]; int dz2 = stoi(s11);
			std::string s12 = argv[rozkaz + 12]; int mm2 = stoi(s12);
			std::string s13 = argv[rozkaz + 13]; int r2 = stoi(s13);
			wyciag(pHead, pHead2,"nazwa.txt" ,id, s, m, g, dz, mm, r, sek2, m2, g2, dz2, mm2, r2);
			rozkaz += 14;
		}
		else if (s == "-undo" && rozkaz + 5 < argc) {
			std::string s2 = argv[rozkaz + 1];
			std::string s3 = argv[rozkaz + 2];
			std::string s4 = argv[rozkaz + 3];
			std::string s5 = argv[rozkaz + 4];
			std::string s6 = argv[rozkaz + 5];
			int id = stoi(s2);
			int dzien = stoi(s3);
			int miesiac = stoi(s4);
			int rok = stoi(s5);
			int kwota = stoi(s6);
			usuniecieTransakcji(pHead, id, dzien, miesiac, rok, kwota);
			rozkaz += 6;
		}
		else if (s == "-wywe" && rozkaz + 3 < argc) {
			std::string s2 = argv[rozkaz + 1];
			std::string s3 = argv[rozkaz + 2];
			std::string s4 = argv[rozkaz + 3];
			int adr = stoi(s2); int odb = stoi(s3); int kwota = stoi(s4);
			przelew(pHead, adr, odb, kwota);
			rozkaz += 4;
		}
		else if (s == "-rT" && rozkaz + 13 < argc) {
			std::string poczym = argv[rozkaz + 1];
			const char* nazwa = argv[rozkaz + 2];
			std::string s2 = argv[rozkaz + 3]; int s = stoi(s2);
			std::string s3 = argv[rozkaz + 4]; int m = stoi(s3);
			std::string s4 = argv[rozkaz + 5]; int g = stoi(s4);
			std::string s5 = argv[rozkaz + 6]; int dz = stoi(s5);
			std::string s6 = argv[rozkaz + 7]; int mm = stoi(s6);
			std::string s7 = argv[rozkaz + 8]; int r = stoi(s7);
			std::string s8 = argv[rozkaz + 9]; int sek2 = stoi(s8);
			std::string s9 = argv[rozkaz + 10]; int m2 = stoi(s9);
			std::string s10 = argv[rozkaz + 11]; int g2 = stoi(s10);
			std::string s11 = argv[rozkaz + 12]; int dz2 = stoi(s11);
			std::string s12 = argv[rozkaz + 13]; int mm2 = stoi(s12);
			std::string s13 = argv[rozkaz + 14]; int r2 = stoi(s13);
			zapiszWszystkieOperacjeWDanymOkresie(pHead, poczym , nazwa, s, m, g, dz, mm, r, sek2, m2, g2, dz2, mm2, r2);
			rozkaz += 14;
		}
		else if (s == "-rD" && rozkaz +1 <argc) {
			const char* nazwa = argv[rozkaz + 1];
			wyswietlWyciagKazdegoZDebetem(pHead, pHead2, nazwa);
			rozkaz += 2;
		}
		else {
			std::cout << "Wprowadzono nieprawidlowe parametry!" << std::endl;
			return 0;
		}

	}

	UPDATE(pHead, UPDATE11);
	ALL(pHead);
	return 0;
}