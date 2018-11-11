#pragma once
#include "Wydarzenie.h"
#include "InputException.h"
#include "vector"
#include "iomanip"
#include "cstdlib"
#include "Lista.h"
#include "BrakException.h"
#include "Sledzone.h"
#include "livestream.h"
#include "iostream"
#include "string"
#include "fstream"
#include "limits"
#include "Serial.h"
#include "ctype.h"
#include "film.h"

class Pula {
private:
	//vector <Wydarzenie*> wydarzenie;
	Sledzone *sle;
	Lista *obj;
	char wybor;

public:
	Pula(Lista *obj, Sledzone *s);
	void wyswietl_liste();
	void petla();
	//void operator += (Wydarzenie* w);
	//bool operator -= (string t);
	void zapisywanie_do_pliku();
	int szukaj(string t);
	void odczytywanie_z_pliku();
	void wyswietl_szczegolowe();
	void oszacuj_sledzone();
	void przypomnienie();
	~Pula();
};

