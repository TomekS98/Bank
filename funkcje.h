#pragma once
/** @file */
#ifndef funkcje_h
#define funkcje_h
#include "struktury.h"
/** Funkcja dodaje dane do listy danych
@param id id uzytkownika
@param imie imie uzytkownika
@param nazw nazwisko uzytkownika
@param PESEL pesel uzytkownika
@param statusK status konta uzytkownika
@param debet debet uzytkownika
@param pHead wskaznik na pierwszy element listy danych
*/
void dodajDoDane(int id, std::string imie, std::string nazw, std::string PESEL, int statusK, int debet, dane*&pHead);
/** Funkcja szuka uzytkownika po id
@param TMP wskaznik na pierwszy elementy listy danych
@param id id uzytkownika
@return uzytkownika o podanym id
*/
dane* znajdzUzytkownikaPoId(dane*TMP, int id);
/** Funkcja zwraca ilosc uzytkownikow w systemie
@param pHead wskaznik na pierwszy element listy danych
@return ilosc uzytkownikow
*/
int iloscUzytkownikow(dane*pHead);
/** Funkcja porownuje dwie transakcje na podstawie daty
@param pNew wskaznik na pierwsza transakcje
@param TMP wskaznik na druga transakcje
@return informacja o tym czy pierwsza transakcja miala miejsce wczesniej niz druga
*/
bool porownaj(transakcja* pNew, transakcja* TMP);
/** Funkcja dodaje transakcje na poczatej listy
@param pHead wskaznik na pierwszy element transakcji
@param pNew wskaznik na dodawany element
*/
void dodajNaPoczTransakcji(transakcja*&pHead, transakcja*pNew);
/** Funkcja dodaje transakcje do listy
@param kwota kwota dodawanej transakcji
@param sekundy sekundy dodawanej transakcji
@param minuty minuty dodawanej transakcji
@param godziny godziny dodawanej transakcji
@param dzien dzien dodawanej transakcji
@param miesiac miesiac dodawanej transakcji
@param rok rok dodawanej transakcji
*/
void dodajTransakcje(transakcja*&pHead, int kwota, int sekundy = 0, int minuty = 0, int godziny = 0, int dzien = 0, int miesiac = 0, int rok = 0);
/** Funkcja dodaje transakcje do uzytkownika
@param pHead wskaznik na pierwszy element listy danych
@param kwota kwota dodawanej transakcji
@param sekundy sekundy dodawanej transakcji
@param minuty minuty dodawanej transakcji
@param godziny godziny dodawanej transakcji
@param dzien dzien dodawanej transakcji
@param miesiac miesiac dodawanej transakcji
@param rok rok dodawanej transakcji
*/
void dodajTransakcjeDoUzytkownika(dane*&pHead, int id, int kwota, int sekundy = 0, int minuty = 0, int godziny = 0, int dzien = 0, int miesiac = 0, int rok = 0);
/** Funkcja sprawdzala wprowadzane dane podczas testowania w debugu
@param x zmienna do sprawdzenia
*/
int sprawdzCIN(int& x);
/** Funkcja aktualizuje stan konta oraz wywoluje funkcje dodawania transakcji
@param pHead wskaznik na poczatek listy danych
@param id id uzytkownika
@param kwota kwota ktora chcemy wplacic na konto uzytkownika
*/
void wplata(dane*pHead, int id, int kwota = 0);
/** Funkcja aktualizuje stan konta oraz wywoluje funkcje dodawania transakcji
@param pHead wskaznik na poczatek listy danych
@param id id uzytkownika
@param kwota kwota ktora chcemy wyplacic na konto uzytkownika
*/
void wyplata(dane*pHead, int id, int kwota = 0);
/**Funkcja sortuje liste danych po ID
@param pHead wskaznik na poczatek listy danych
*/
void posortujpoID(dane*&pHead);
/**Funkcja sortuje liste danych zalezne od nazwiska leksykograficznie oraz wypisuje je do pliku. Parametry potrzebne do wywolania funkcji wyciag.
@param pHead wskaznik na poczatek listy danych
@param nazwa nazwa pliku
@param s sekundy pocz¹tku transakcji
@param m minuty pocz¹tku transakcji
@param g godziny pocz¹tku transakcji
@param dz dzien pocz¹tku transakcji
@param mm miesiac pocz¹tku transakcji
@param r rok pocz¹tku transakcji
@param s2 sekundy koñca transakcji
@param m2 minuty koñca transakcji
@param g2 godziny koñca transakcji
@param dz2 dzien koñca transakcji
@param mm2 miesiac koñca transakcji
@param r2 rok koñca transakcji
*/
void posortujpoNAZW(dane*&pHead, const char*nazwa, int s, int m, int g, int dz, int mm, int r, int s2, int m2, int g2, int dz2, int mm2, int  r2);
/** Funkcja wykorzystuje funkcje wyplac i wplac pobiera aktualny czas zegaru systemowego.
@param adr id adresata
@param odb id odbiorcy
@param kwota kwota jaka chcemy przelac
*/
void przelew(dane*pHead, int adr, int odb, int kwota);
/** Funkcja zapisuje transakcje do pliku pomiedzy podanymi datami ktore przechowuja wskazniki pStart i pEnd
@param pHead wskaznik na poczatek listy transakcji
@param pStart wskaznik przechowywujacy date ograniczajaca od dolu
@param pEnd wskaznik przechowywujacy date ograniczajaca od gory
@param nazwa nazwa pliku tekstowego do zapisu
*/
void wyswietlTransakcjePomiedzyDatami(transakcja* pHead, transakcja*pStart, transakcja*pEnd, const char * nazwa = "nazwa.txt");
/** Funkcja ktora wypisuje dane poszczegolnej osoby w konsoli albo do pliku
@param pHead2 wskaznik na pierwszy element listy danych
@param pHead wskaznik na pierwszy element listy transakcji
@param id id uzytkownika
@param nazwa nazwa pliku tekstowego do zapisu
@param s sekundy pocz¹tku transakcji
@param m minuty pocz¹tku transakcji
@param g godziny pocz¹tku transakcji
@param dz dzien pocz¹tku transakcji
@param mm miesiac pocz¹tku transakcji
@param r rok pocz¹tku transakcji
@param s2 sekundy koñca transakcji
@param m2 minuty koñca transakcji
@param g2 godziny koñca transakcji
@param dz2 dzien koñca transakcji
@param mm2 miesiac koñca transakcji
@param r2 rok koñca transakcji
*/
void wyciag(dane*pHead2, transakcja*pHead, const char*nazwa = "nazwa.txt", int id = 0, int s = 0, int m = 0, int g = 0, int dz = 0, int mm = 0, int r = 0, int s2 = 0, int m2 = 0, int g2 = 0, int dz2 = 0, int mm2 = 0, int r2 = 0);
/**Funkcja usuwajaca transakcje o ile istnieje o podanej dacie i kwocie
@param pHead wskaznik na pierwszy element listy danych
@param dzien dzien 
@param miesiac miesiac
@param rok rok
@param kwota o jakiej ma zostac usunieta transakcja
*/
void usuniecieTransakcji(dane*&pHead, int id, int dzien = 0, int miesiac = 0, int rok = 0, int kwota = 0);
/**  zapisuje wszystkie transakcje w danym okresie do pliku po nazw leksykograficznie albo po id rosnaco
@param pHead wskaznik na pierwszy element listy danych
@param poczym informacja po czym posortowac liste danych powinna przyjmowaæ albo "id" albo "nazw" aby sortowanie bylo odpowiednio po id albo leksykograficznie po nazwiskach
@param nazwa nazwa pliku tekstowego do zapisu
@param s sekundy pocz¹tku transakcji
@param m minuty pocz¹tku transakcji
@param g godziny pocz¹tku transakcji
@param dz dzien pocz¹tku transakcji
@param mm miesiac pocz¹tku transakcji
@param r rok pocz¹tku transakcji
@param s2 sekundy koñca transakcji
@param m2 minuty koñca transakcji
@param g2 godziny koñca transakcji
@param dz2 dzien koñca transakcji
@param mm2 miesiac koñca transakcji
@param r2 rok koñca transakcji
*/
void zapiszWszystkieOperacjeWDanymOkresie(dane*&pHead, std::string poczym,const char * nazwa, int s = 0, int m = 0, int g = 0, int dz = 0, int mm = 0, int r = 0, int s2 = 0, int m2 = 0, int g2 = 0, int dz2 = 0, int mm2 = 0, int r2 = 0);
/**Funkcja zapisuje wszystkie transakcje danego uzytkownika do pliku
@param pHead wskaznik na pierwszy element transakcji
@param nazwa nazwa pliku tekstowego do zapisy
*/
void wyswietlTransakcje(transakcja* pHead, const char * nazwa = "nazwa.txt");
/**Funkcja uaktualnia wczesniej wprowadzony plik tekstowy
@param pHead wskaznik na pierwszy element listy danych
@param nazwa nazwa pliku tekstowego
*/
void UPDATE(dane* pHead, const char * nazwa = "nazwa.txt");
/** Funkcja zapisuje kazdego z debetem do pliku tekstowego
@param pHead wskaznik na pierwszy element listy danych/
@param pHead2 wskaznik na pierwszy element listy transakcji
@param nazwa nazwa pliku tekstowego
*/
void wyswietlWyciagKazdegoZDebetem(dane*pHead, transakcja*pHead2, const char* nazwa);
/** Funkcja ofczytujaca dane z pliku tekstowego
@param pHead wskaznik na pierwszy element listy danych
@param nazwa nazwa pliku tekstowego
*/
void odczytZPliku(dane*&pHead, const char * nazwa);
/** Funkcja usuwajaca wszystkie transakcje danego uzytkownika
@param pHead wskaznik na pierwsza transakcjde danego uzytkownika
*/
void usunALLtrans(transakcja*&pHead);
/**Fukcja usuwajaca wszystkie dane wywoluje funkcje usunALLtrans
@param pHead wskaznik na pocztake listy danych
*/
void ALL(dane*&pHead);
#endif //funckje_h
