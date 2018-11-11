#pragma once
#include "Wydarzenie.h"
#include "Pula.h"
class Serial :
	public Wydarzenie {
private:
	int liczba_odcinkow = 0, liczba_obejrzanych_odcinkow = 0, liczba_sezonow = 0, srednia_dl_odc = 0;
public:
	Serial();
	Serial(string nazwa, string gatunek, int l_s, int l_odc, int l_obej, int s_d_o, float ocena, bool s);
	void wyswietl();
	void zapisz(string file);
	void wyswietl_dokladne();
	void edytuj();
	int get_dlugosc();
	int wpisz_dane(int min, int max);
	float wpisz_dane_f();
	~Serial();
};

