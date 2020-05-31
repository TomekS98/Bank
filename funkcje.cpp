#include "struktury.h"
#include "funkcje.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

void dodajDoDane(int id, std::string imie, std::string nazw, std::string PESEL, int statusK, int debet, dane*&pHead) {
	dane*pNew = new dane{ id,imie,nazw,PESEL,statusK,debet,NULL,NULL };
	dane*TMP = pHead;
	if (TMP) {
		while (TMP->pNext)
			TMP = TMP->pNext;
		TMP->pNext = pNew;
	}
	else
		pHead = pNew;
}

dane* znajdzUzytkownikaPoId(dane*TMP, int id) {
	while (TMP) {
		if (TMP->id == id)
			break;
		TMP = TMP->pNext;
	}
	return TMP;
}
int iloscUzytkownikow(dane*pHead) {
	int iloscID = 0;
	while (pHead) {
		iloscID++;
		pHead = pHead->pNext;

	}
	return iloscID;
}

bool porownaj(transakcja* pNew, transakcja* TMP)
{
	if (pNew->rok != TMP->rok)
		return pNew->rok < TMP->rok;
	if (pNew->miesiac != TMP->miesiac)
		return pNew->miesiac < TMP->miesiac;
	if (pNew->dzien != TMP->dzien)
		return pNew->dzien < TMP->dzien;
	if (pNew->godziny != TMP->godziny)
		return pNew->godziny < TMP->godziny;
	if (pNew->minuty != TMP->minuty)
		return pNew->minuty < TMP->minuty;
	if (pNew->sekundy != TMP->sekundy)
		return pNew->sekundy < TMP->sekundy;
	return false;
}

void dodajNaPoczTransakcji(transakcja*&pHead, transakcja*pNew) {
	pNew->pNext = pHead;
	pHead = pNew;
}
void dodajTransakcje(transakcja*&pHead, int kwota, int sekundy, int minuty, int godziny, int dzien, int miesiac, int rok) {
	if (rok == 0 || miesiac == 0 || dzien == 0) {
		struct tm newTime;
		time_t now = time(0);
		localtime_s(&newTime, &now);
		int sekundy = 1 + newTime.tm_sec;
		int minuty = 1 + newTime.tm_min;
		int godziny = newTime.tm_hour;
		int dzien = newTime.tm_mday;
		int miesiac = 1 + newTime.tm_mon;
		int rok = 1900 + newTime.tm_year;
		transakcja* pNew = new transakcja{ sekundy, minuty,godziny,dzien,miesiac,rok,kwota,NULL };
		transakcja* TMP = pHead;
		if (!TMP)
			pHead = pNew;
		else {
			if (porownaj(pNew, TMP) == true) {
				pNew->pNext = pHead;
				pHead = pNew;
			}
			else {
				while (TMP->pNext) {
					if (porownaj(pNew, TMP->pNext) == true)
						break;
					TMP = TMP->pNext;
				}
				if (!(TMP->pNext))
					TMP->pNext = pNew;
				else {
					pNew->pNext = TMP->pNext;
					TMP->pNext = pNew;
				}
			}
		}
		return;
	}
	transakcja* pNew = new transakcja{ sekundy, minuty,godziny,dzien,miesiac,rok,kwota,NULL };
	transakcja* TMP = pHead;
	if (!TMP)
		pHead = pNew;
	else {
		if (porownaj(pNew, TMP) == true) {
			pNew->pNext = pHead;
			pHead = pNew;
		}
		else {
			while (TMP->pNext) {
				if (porownaj(pNew, TMP->pNext) == true)
					break;
				TMP = TMP->pNext;
			}
			if (!(TMP->pNext))
				TMP->pNext = pNew;
			else {
				pNew->pNext = TMP->pNext;
				TMP->pNext = pNew;
			}
		}
	}
}

void dodajTransakcjeDoUzytkownika(dane*&pHead, int id, int kwota, int sekundy, int minuty, int godziny, int dzien, int miesiac, int rok) {
	dane*TMP = pHead;
	if (!TMP)
		std::cout << "Brak u¿ytkowników w systemie!" << std::endl;
	else {
		TMP = znajdzUzytkownikaPoId(pHead, id);
		if (TMP->id == id) {
			dodajTransakcje(TMP->pHead, kwota, sekundy, minuty, godziny, dzien, miesiac, rok);
		}
		else
			std::cout << "Brak u¿ytkownika o takim ID!";
	}
}
int sprawdzCIN(int& x) {
	while (!(std::cin >> x)) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Upewnij sie czy poprawnie wprowadzono dane!" << std::endl << " Sprobuj ponownie." << std::endl;
	}
	return x;
}
void wplata(dane*pHead, int id, int kwota) {
	if (kwota == 0) {
		std::cout << "Podaj jaka kwote chcesz wplacic: " << std::endl;
		kwota = sprawdzCIN(kwota);
	}
	dodajTransakcjeDoUzytkownika(pHead, id, kwota);
	dane*TMP = znajdzUzytkownikaPoId(pHead, id);
	if (TMP->id == id) {
		if (TMP->debet == 0) {
			TMP->statusK += kwota;
			std::cout << "Wplacono na konto " << TMP->imie << " " << TMP->nazw << " kwote o wysokosci " << kwota << "zl.Stan konta wynosi: " << TMP->statusK << "zl." << std::endl;
		}
		else if (TMP->debet > kwota) {
			TMP->debet -= kwota;
			std::cout << "Splacono " << kwota << "zl debetu. Na koncie " << TMP->imie << " " << TMP->nazw << " zostal debet w wysokosci " << TMP->debet << "zl." << std::endl;
		}
		else if (TMP->debet > 0 && TMP->debet < kwota) {
			int kwota1 = kwota - (TMP->debet);
			TMP->debet = 0;
			TMP->statusK += kwota1;
			std::cout << "Splacono caly debet. Na konto " << TMP->imie << " " << TMP->nazw << " srodki o wartosci " << kwota1 << "zl." << std::endl;
		}
	}

}


void wyplata(dane*pHead, int id, int kwota) {
	dane*TMP = znajdzUzytkownikaPoId(pHead, id);
	if (!TMP) return;
	if (TMP->id != id)
		std::cout << "Brak u¿ytkownika o takim ID" << std::endl;
	else {
		if (kwota == 0) {
			std::cout << "Podaj kwote, ktora chcesz wyplacic na konto " << TMP->imie << " " << TMP->nazw << ":\n";
			kwota = sprawdzCIN(kwota);
		}
		if (((TMP->debet) + kwota) - (TMP->statusK) > 1000) {
			std::cout << "Debet na koncie wyniesie wiecej niz 1000zl!" << std::endl;
			return;
		}
		else {
			if (kwota <= TMP->statusK){
				TMP->statusK -= kwota;
				std::cout << "Wyplacono z konta " << TMP->imie << " " << TMP->nazw << " " << kwota << "zl. Na koncie zostalo " << TMP->statusK << "zl." << std::endl;
				dodajTransakcjeDoUzytkownika(TMP, id, -kwota);
		}
			else {
				int kwota2 = kwota;
				kwota2 -= TMP->statusK;
				TMP->statusK = 0;
				TMP->debet += kwota2;
				std::cout << "Wyplacono z konta " << TMP->imie << " " << TMP->nazw << " " << kwota << "zl. Na koncie zostalo 0zl z debetem " << TMP->debet << "zl." << std::endl;
				dodajTransakcjeDoUzytkownika(TMP, id, -kwota);
			}
			//}
		}
	}

}

void przelew(dane*pHead, int adr, int odb, int kwota) {
	if (adr == odb) return;
	wyplata(pHead, adr, kwota);
	wplata(pHead, odb, kwota);
}
void wyswietlTransakcjePomiedzyDatami(transakcja* pHead, transakcja*pStart, transakcja*pEnd, const char * nazwa) {
	std::fstream plik;
	plik.open(nazwa, std::ios::in | std::ios::out | std::ios::ate);

	while (pHead)
	{
		if (nazwa == "nazwa.txt") {
			if (porownaj(pStart, pHead) == true && porownaj(pHead, pEnd) == true)
				std::cout << pHead->dzien << " " << pHead->miesiac << " " << pHead->rok << " " << "godzina: " << pHead->godziny << ":" << pHead->minuty << ":" << pHead->sekundy << "     Kwota transakcji: " << pHead->kwota << std::endl;
		}
		else {
			if (porownaj(pStart, pHead) == true && porownaj(pHead, pEnd) == true)
				plik << pHead->dzien << " " << pHead->miesiac << " " << pHead->rok << " " << "godzina: " << pHead->godziny << ":" << pHead->minuty << ":" << pHead->sekundy << "     Kwota transakcji: " << pHead->kwota << std::endl;

		}
		pHead = pHead->pNext;
	}
	std::cout << std::endl;
}

void wyciag(dane*pHead2, transakcja*pHead, const char*nazwa, int id, int s, int m, int g, int dz, int mm, int r, int s2, int m2, int g2, int dz2, int mm2, int r2) {
	if (id == 0) {
		std::cout << "Podaj id od 1 do " << iloscUzytkownikow(pHead2) << ":";
		id = sprawdzCIN(id);
		std::cout << std::endl;
	}
	dane*TMP = znajdzUzytkownikaPoId(pHead2, id);
	if (TMP->id != id)
		std::cout << "Nie ma uzytkownika o takim id" << std::endl;
	else {
		if (dz == 0 || mm == 0 || r == 0) {
			std::cout << "Podaj kolejno sekunde, minute, godzine, dzien, miesiac, rok od kiedy chcesz wyciag." << std::endl;
			s = sprawdzCIN(s);
			m = sprawdzCIN(m);
			g = sprawdzCIN(g);
			dz = sprawdzCIN(dz);
			mm = sprawdzCIN(mm);
			r = sprawdzCIN(r);
		}
		if (dz2 == 0 || mm2 == 0 || r2 == 0) {
			std::cout << "Podaj kolejno sekunde, minute, godzine, dzien, miesiac, rok do kiedy chcesz wyciag." << std::endl;
			s2 = sprawdzCIN(s2);
			m2 = sprawdzCIN(m2);
			g2 = sprawdzCIN(g2);
			dz2 = sprawdzCIN(dz2);
			mm2 = sprawdzCIN(mm2);
			r2 = sprawdzCIN(r2);
		}
		transakcja*TMPStart = new transakcja{ s,m,g,dz,mm,r,0,NULL };
		transakcja*TMPEnd = new transakcja{ s2,m2,g2,dz2,mm2,r2,0,NULL };
		transakcja*TMP2 = TMP->pHead;
		if (nazwa == "nazwa.txt") {
			std::fstream plik;
			plik.open(nazwa, std::ios::in | std::ios::out | std::ios::ate);
			plik.close();
			std::cout << "id: " << TMP->id << std::endl;
			std::cout << "imie: " << TMP->imie << std::endl;
			std::cout << "nazwisko: " << TMP->nazw << std::endl;
			std::cout << "pesel: " << TMP->PESEL << std::endl;
			std::cout << "status konta: " << TMP->statusK << std::endl;
			std::cout << "debet: " << TMP->debet << std::endl;
			std::cout << "lista transakcji pomiedzy: " << TMPStart->dzien << "-" << TMPStart->miesiac << "-" << TMPStart->rok << " " << TMPStart->sekundy << ":" << TMPStart->minuty << ":" << TMPStart->godziny << "   a   ";
			std::cout << TMPEnd->dzien << "-" << TMPEnd->miesiac << "-" << TMPEnd->rok << " " << TMPEnd->sekundy << ":" << TMPEnd->minuty << ":" << TMPEnd->godziny << std::endl;
			if (!TMP2)
				std::cout << "Brak!" << std::endl << std::endl;
			else
				wyswietlTransakcjePomiedzyDatami(TMP2, TMPStart, TMPEnd, nazwa);
		}
		else {
			std::fstream plik;
			plik.open(nazwa, std::ios::in | std::ios::out | std::ios::ate);
			plik << "id: " << TMP->id << std::endl;
			plik << "imie: " << TMP->imie << std::endl;
			plik << "nazwisko: " << TMP->nazw << std::endl;
			plik << "pesel: " << TMP->PESEL << std::endl;
			plik << "status konta: " << TMP->statusK << std::endl;
			plik << "debet: " << TMP->debet << std::endl;
			plik << "lista transakcji pomiedzy: " << TMPStart->dzien << "-" << TMPStart->miesiac << "-" << TMPStart->rok << " " << TMPStart->sekundy << ":" << TMPStart->minuty << ":" << TMPStart->godziny << "   a   ";
			plik << TMPEnd->dzien << "-" << TMPEnd->miesiac << "-" << TMPEnd->rok << " " << TMPEnd->sekundy << ":" << TMPEnd->minuty << ":" << TMPEnd->godziny << std::endl;
			plik.close();
			if (!TMP2)
				std::cout << "Brak!" << std::endl << std::endl;
			else {
				wyswietlTransakcjePomiedzyDatami(TMP2, TMPStart, TMPEnd, nazwa);
			}
			plik.close();
		}
		delete TMPStart;
		delete TMPEnd;
	}
}

void posortujpoID(dane*&pHead) {
	if (pHead->pNext) {
		dane*TMP = pHead;
		dane*TMP2 = pHead->pNext;
		dane*TMP3 = pHead;
		int a = 1;
		while (a > 0) {
			a = 0;
			TMP = pHead;
			TMP2 = pHead->pNext;
			while (TMP2) {
				if (TMP->id > TMP2->id) {
					if (TMP2 == pHead->pNext)
						pHead = TMP2;
					std::swap(TMP->pNext, TMP2->pNext);
					a++;
				}
				if (!TMP2->pNext)
					break;
				TMP = TMP2;
				TMP2 = TMP2->pNext;
			}
		}
	}
}

void posortujpoNAZW(dane*&pHead, const char*nazwa, int s, int m, int g, int dz, int mm, int r, int s2, int m2, int g2, int dz2, int mm2, int  r2) {
	if (pHead && pHead->pNext && pHead->pNext->pNext) {
		dane*TMP = pHead;
		dane*TMP2 = pHead->pNext;
		dane*TMP3 = pHead->pNext->pNext;
		int a = 1;
		int m = 0;
		while (a > 0) {
			a = 0;
			m = 0;
			while (TMP3) {
				if (m == 0) {
					if (TMP->nazw > TMP2->nazw) {
						TMP->pNext = TMP3;
						TMP2->pNext = TMP;
						pHead = TMP2;
						TMP = pHead;
						TMP2 = pHead->pNext;
						TMP3 = pHead -> pNext -> pNext;
						a++;
					}
				}
				else {
					if (TMP2->nazw > TMP3->nazw) {
						TMP->pNext = TMP3;
						TMP2->pNext = TMP3->pNext;
						TMP3->pNext = TMP2;
						a++;
					}
					if (!TMP2->pNext)
						break;
					TMP = TMP2;
					TMP2 = TMP3;
					if(TMP3->pNext)
					TMP3 = TMP3->pNext;
				}
				m++;
			}
			TMP = pHead;
			TMP2 = pHead->pNext;
			TMP3 = pHead->pNext->pNext;
		}
		while (TMP) {
			wyciag(pHead, pHead->pHead, nazwa, TMP->id, s, m, g, dz, mm, r, s2, m2, g2, dz2, mm2, r2);
			TMP = TMP->pNext;
		}
	}
	else if (pHead && pHead->pNext) {
		if (pHead->nazw > pHead->pNext -> nazw) {
			dane* TMP = pHead->pNext;
			pHead->pNext->pNext = pHead;
			pHead->pNext = NULL;
			pHead = TMP;
		}
		dane*TMP = pHead;
		while (TMP) {
			wyciag(pHead, pHead->pHead, nazwa, TMP->id, s, m, g, dz, mm, r, s2, m2, g2, dz2, mm2, r2);
			TMP = TMP->pNext;
		}
	}
}

void usuniecieTransakcji(dane*&pHead, int id, int dzien, int miesiac, int rok, int kwota) {
	if (miesiac < 1 || miesiac>12 || dzien < 1 || dzien>31) {
		std::cout << "Zle podano miesiac lub dzien! Sprobuj ponownie." << std::endl;
		return;
	}
	else {
		dane*TMPid = znajdzUzytkownikaPoId(pHead, id);
		if (!TMPid) return;
		transakcja*TMP = TMPid->pHead;
		if (!TMP) {
			std::cout << "Brak transakcji do usuniecia." << std::endl;
			return;
		}
		if (TMP->rok == rok && TMP->miesiac == miesiac && TMP->dzien == dzien && TMP->kwota == kwota && TMP->pNext) {
			transakcja*TMPdousuniecia = TMP;
			pHead->pHead = TMP->pNext;
			delete TMPdousuniecia;
			std::cout << "Pomyslnie usunieto transakcje." << std::endl;
		}
		else {
			while (TMP->pNext) {
				if (TMP->pNext->rok == rok && TMP->pNext->miesiac == miesiac && TMP->pNext->dzien == dzien && TMP->pNext->kwota == kwota) {
					std::cout << "Pomyslnie usunieto transakcje." << std::endl;
					transakcja*TMP2 = TMP->pNext;
					TMP->pNext = TMP->pNext->pNext;
					delete TMP2;
					return;
				}
				TMP = TMP->pNext;
			}
		}
	}
}


void zapiszWszystkieOperacjeWDanymOkresie(dane*&pHead, std::string poczym,const char * nazwa, int s, int m, int g, int dz, int mm, int r, int s2, int m2, int g2, int dz2, int mm2, int r2){
	std::fstream plik;
	plik.open(nazwa, std::ios::out | std::ios::trunc);
	plik.close();
	if (dz == 0 || mm == 0 || r == 0 || dz2 == 0 || mm2 == 0 || r2 == 0) {
		std::cout << "Podaj kolejno sekunde, minute, godzine, dzien, miesiac, rok od kiedy chcesz wyciag." << std::endl;
		s = sprawdzCIN(s);
		m = sprawdzCIN(m);
		g = sprawdzCIN(g);
		dz = sprawdzCIN(dz);
		mm = sprawdzCIN(mm);
		r = sprawdzCIN(r);
		std::cout << "Podaj kolejno sekunde, minute, godzine, dzien, miesiac, rok do kiedy chcesz wyciag." << std::endl;
		s2 = sprawdzCIN(s2);
		m2 = sprawdzCIN(m2);
		g2 = sprawdzCIN(g2);
		dz2 = sprawdzCIN(dz2);
		mm2 = sprawdzCIN(mm2);
		r2 = sprawdzCIN(r2);
	}
	if (poczym == "nazw") {
		posortujpoNAZW(pHead, nazwa, s,m,g,dz,mm,r,s2,m2,g2,dz2,mm2,r2);
	}
	else {
		int id = 1;
		while (id <= iloscUzytkownikow(pHead)) {
			wyciag(pHead, pHead->pHead, nazwa, id, s, m, g, dz, mm, r, s2, m2, g2, dz2, mm2, r2);
			id++;
		}
	}
}

void wyswietlTransakcje(transakcja* pHead, const char * nazwa) {
	while (pHead)
	{
		if (nazwa == "nazwa.txt")
			std::cout << pHead->dzien << " " << pHead->miesiac << " " << pHead->rok << " " << "godzina: " << pHead->godziny << ":" << pHead->minuty << ":" << pHead->sekundy << "     Kwota transakcji: " << pHead->kwota << std::endl;
		else {
			std::fstream plik;
			plik.open(nazwa, std::ios::out | std::ios::in | std::ios::ate);
			plik << pHead->dzien << "-" << pHead->miesiac << "-" << pHead->rok << " " << pHead->godziny << ":" << pHead->minuty << ":" << pHead->sekundy << " " << pHead->kwota << std::endl;
			plik.close();
		}
		pHead = pHead->pNext;
	}
	if (nazwa == "nazwa.txt")
		std::cout << std::endl;

}

void UPDATE(dane* pHead, const char * nazwa){
	std::fstream plik;
	plik.open(nazwa, std::ios::out | std::ios::trunc);
	plik.close();
	while (pHead)
	{
		if (nazwa == "nazwa.txt") {
			std::cout << "id: " << pHead->id << std::endl;
			std::cout << "imie: " << pHead->imie << std::endl;
			std::cout << "nazwisko: " << pHead->nazw << std::endl;
			std::cout << "pesel: " << pHead->PESEL << std::endl;
			std::cout << "status konta: " << pHead->statusK << std::endl;
			std::cout << "debet: " << pHead->debet << std::endl;
			std::cout << "lista transakcji: " << std::endl;
			if (!pHead->pHead)
				std::cout << "Brak!" << std::endl << std::endl;
			else
				wyswietlTransakcje(pHead->pHead, nazwa);
		}
		else {
			std::fstream plik;
			plik.open(nazwa, std::ios::out | std::ios::in | std::ios::ate);
			plik << pHead->id << " " << pHead->imie << " " << pHead->nazw << " " << pHead->PESEL << " " << pHead->statusK << " " << pHead->debet << std::endl;
			plik.close();
			if (pHead->pHead)
				wyswietlTransakcje(pHead->pHead, nazwa);
			else {
				std::fstream plik;
				plik.open(nazwa, std::ios::out | std::ios::in | std::ios::ate);
				plik << "=-" << std::endl;
			}
			if (pHead->pNext) {
				std::fstream plik;
				plik.open(nazwa, std::ios::out | std::ios::in | std::ios::ate);
				plik << "=-" << std::endl;
				plik.close();
			}
		}
		pHead = pHead->pNext;
	}
}

void wyswietlWyciagKazdegoZDebetem(dane*pHead, transakcja*pHead2, const char* nazwa) {
	std::ofstream plik(nazwa);
	int id = 1;
	dane*TMP;
	transakcja*TMP2;
	while (id <= iloscUzytkownikow(pHead)) {
		TMP = znajdzUzytkownikaPoId(pHead, id);
		TMP2 = TMP->pHead;

		if (TMP->debet != 0) {
			plik << "Wyciag z konta " << TMP->imie << " " << TMP->nazw << std::endl;
			while (TMP2)
			{
				plik << TMP2->dzien << " " << TMP2->miesiac << " " << TMP2->rok << " " << "godzina: " << TMP2->godziny << ":" << TMP2->minuty << ":" << TMP2->sekundy << "     Kwota transakcji: " << TMP2->kwota << std::endl;
				TMP2 = TMP2->pNext;
			}
		}
		id++;
	}
}

void odczytZPliku(dane*&pHead, const char * nazwa) {
	std::ifstream plik(nazwa);
	if (!plik || !plik.is_open())
		std::cout << "Nie ma pliku o takiej nazwie." << std::endl;
	int id, statusK, debet, kwota, s, m, g, dz, mm, r;
	std::string imie, nazw, pesel, zmienna;

	while (!plik.eof()) {
		plik >> id >> imie >> nazw >> pesel >> statusK >> debet;
		std::cout << id << " " << imie << " " << nazw << " " << pesel << " " << statusK << " " << debet << std::endl;
		dodajDoDane(id, imie, nazw, pesel, statusK, debet, pHead);
		while (!plik.eof()) {
			getline(plik, zmienna, '-');
			if (plik.eof() || zmienna == "=")
				break;
			dz = stoi(zmienna);
			getline(plik, zmienna, '-'); mm = stoi(zmienna);
			getline(plik, zmienna, ' '); r = stoi(zmienna);
			getline(plik, zmienna, ':'); g = stoi(zmienna);
			getline(plik, zmienna, ':'); m = stoi(zmienna);
			getline(plik, zmienna, ' '); s = stoi(zmienna);
			getline(plik, zmienna); kwota = stoi(zmienna);
			dodajTransakcjeDoUzytkownika(pHead, id, kwota, s, m, g, dz, mm, r);
		}
	}
}
void usunALLtrans(transakcja*&pHead) {
	transakcja*TMP;
	while (pHead) {
		TMP = pHead;
		pHead = pHead->pNext;
		delete TMP;
	}
	pHead = NULL;
}
void ALL(dane*&pHead) {
	dane*TMP;
	while (pHead) {
		if (pHead->pHead) {
			usunALLtrans(pHead->pHead);
		}
		TMP = pHead;
		pHead = pHead->pNext;
		delete TMP;
	}
	pHead = NULL;
}