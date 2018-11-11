#pragma once
#include "iostream"
#include <string>
#include "iomanip"
#include "InputException.h"
#include "LiczbaException.h"
#include "algorithm"
using namespace std;

class Wydarzenie{
protected:
	string nazwa_programu = " ";
	string gatunek = " "; 
	float ocena = 0;
	bool sledzony = false;

public:
	Wydarzenie();
	virtual void wyswietl();
	virtual void zapisz(string file);
	virtual void wyswietl_dokladne();
	virtual void edytuj();
	bool czy_sledzony();
	bool operator == (string t);
	bool operator == (Wydarzenie &w);
	bool sledzenie();
	virtual int get_dlugosc();
	virtual void przypominaj();
	~Wydarzenie();
};

