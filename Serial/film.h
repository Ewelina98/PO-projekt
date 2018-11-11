#pragma once
#include "Wydarzenie.h"
#include "fstream"
class film :
	public Wydarzenie {
private:
	bool czy_obejrzany = false;
	int dlugosc = 0;
public:
	film();
	film(string nazwa, string gatunek, int dlu, float ocena, bool obejrzany, bool sledzone);
	float wpisz_dane_f();
	void zapisz(string t);
	void wyswietl();
	void wyswietl_dokladne();
	int get_dlugosc();
	void edytuj();
	~film();
};

