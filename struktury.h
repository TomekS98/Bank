#pragma once

/** @file */
#include <string>

#ifndef struktury_h
#define struktury_h

/** Lista jednokierunkowa transakcji */
struct transakcja {
	int sekundy; ///< sekundy transakcji
	int minuty; ///< minuty transakcji
	int godziny; ///< godziny transakcji
	int dzien; ///< dzien transakcji
	int miesiac; ///< miesiac transakcji
	int rok; ///< rok transakcji 
	int kwota; ///< kwota transakcji
	transakcja*pNext; ///< wskaznik na nastepna transakcje
};

/** Lista jednokierunkowa z danymi uzytkownikow */
struct dane {
	int id; ///< id uzytkownika
	std::string imie; ///< imie uzytkownika
	std::string nazw; ///< nazwisko uzytkownika
	std::string PESEL; ///< PESEL uzytkownika
	int statusK; ///< stan konta uzytkownika
	int debet; ///< debet uzytkownika
	dane* pNext; ///< wskaznik na nastepny element listy
	transakcja* pHead; ///< wskaznik na transakcje powiazane z uzytkownikiem
};

#endif