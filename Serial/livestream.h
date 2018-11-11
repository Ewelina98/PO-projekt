#pragma once
#include "Wydarzenie.h"
#include "Windows.h"
#include "fstream"
class livestream :
	public Wydarzenie{
private:
	int dzien_wydarzenia, miesiac_wydarzenia, rok_wydarzenia, godzina, minuta;
	int dzisiaj_dzien, dzisiaj_miesiac, dzisiaj_rok, a_godz, a_minuta;
public:
	livestream();
	livestream(string nazwa, string gatunek, float ocena, int dzien, int miesiac, int rok, int h, int m, bool sledz);
	void przypominaj();
	void zapisz(string t);
	void wyswietl();
	void wyswietl_dokladne();
	inline int get_dlugosc() { return -1; }
	void edytuj();
	void ustaw_dzisiaj();
	int wpisz_dane(int maks);
	~livestream();
};

