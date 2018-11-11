#include "Pula.h"
using namespace std;

Pula::Pula(Lista *ob, Sledzone *s) {
	obj = ob;
	sle = s;
 	odczytywanie_z_pliku();
	petla();
}

void Pula::odczytywanie_z_pliku() {
	fstream plik;
	plik.open("lista_seriali.txt", ios::in);
	int liczba_programow_w_puli;
	string typ_wydarzenia = " ";
	string nazwa, gat, ss;
	getline(plik, ss);
	liczba_programow_w_puli = atoi(ss.c_str());
	int l_s, dl, s_l_odc, s_l_obej, s_d_o;
	float ocena;
	bool sledzony, obejrzany;
	int dzien, miesiac, rok, h, min;
	Serial *serial;
	livestream *live;
	film * fil;
	Wydarzenie *w;
	for (int i = 0; i < liczba_programow_w_puli; i++) {
		getline(plik, typ_wydarzenia);
		if (typ_wydarzenia == "s") {
			getline(plik, nazwa);
			getline(plik, gat);
			getline(plik, ss);
			l_s = atoi(ss.c_str());
			getline(plik, ss);
			s_l_odc = atoi(ss.c_str());
			getline(plik, ss);
			s_l_obej = atoi(ss.c_str());
			getline(plik, ss);
			s_d_o = atoi(ss.c_str());
			getline(plik, ss);
			ocena = atof(ss.c_str());
			getline(plik, ss);
			sledzony = atoi(ss.c_str());
			serial = new Serial(nazwa, gat, l_s, s_l_odc, s_l_obej, s_d_o, ocena, sledzony);
			obj->wydarzenie.push_back(serial);
			if (sledzony == 1)	sle->sledzone.push_back(serial);
		}
		if (typ_wydarzenia == "l") {
			getline(plik, nazwa);
			getline(plik, gat);
			getline(plik, ss);
			ocena = atof(ss.c_str());
			getline(plik, ss);
			dzien = atoi(ss.c_str());
			getline(plik, ss);
			miesiac = atoi(ss.c_str());
			getline(plik, ss);
			rok = atoi(ss.c_str());
			getline(plik, ss);
			h = atoi(ss.c_str());
			getline(plik, ss);
			min = atoi(ss.c_str());
			getline(plik, ss);
			sledzony = atoi(ss.c_str());
			live = new livestream(nazwa, gat, ocena, dzien, miesiac, rok, h, min, sledzony);
			obj->wydarzenie.push_back(live);
			if (sledzony == 1)	sle->sledzone.push_back(live);
		}
		if (typ_wydarzenia == "f") {
			getline(plik, nazwa);
			getline(plik, gat);
			getline(plik, ss);
			dl = atoi(ss.c_str());
			getline(plik, ss);
			ocena = atof(ss.c_str());
			getline(plik, ss);
			obejrzany = atoi(ss.c_str());
			getline(plik, ss);
			sledzony = atoi(ss.c_str());
			fil = new film(nazwa, gat, dl, ocena, obejrzany, sledzony);
			obj->wydarzenie.push_back(fil);
			if (sledzony == 1)	sle->sledzone.push_back(fil);
		}
	}
	plik.close();
}

void Pula::zapisywanie_do_pliku() {
	fstream plik;
	plik.open("lista_seriali.txt", ios::trunc | ios::out);
	plik << obj->wydarzenie.size() << endl;
	plik.close();
	for (int i = 0; i < obj->wydarzenie.size(); i++) 	(*(obj->wydarzenie[i])).zapisz("lista_seriali.txt");
}

void Pula::wyswietl_liste() {
	system("cls");
	cout << setw(4) << "Lp." << setw(10) << "Rodzaj" << setw(20) << "Tytul" << setw(15) << "Gatunek" << setw(7) << "Ocena" <<endl;
	for (int i = 0; i < obj->wydarzenie.size(); i++) {
		cout << setw(4) << i + 1;
		(*(obj->wydarzenie[i])).wyswietl();
	}
}

int Pula::szukaj(string t) {
	for (int i = 0; i < obj->wydarzenie.size(); i++)
		if ((*(obj->wydarzenie[i])).operator==(t))
			return i;
	throw	BrakException();
}

void Pula::wyswietl_szczegolowe() {
	cout << "Jakiego tytulu szukac?\n";
	string tytul;
	getline(cin, tytul);
	try {
		int i = szukaj(tytul), f = 0;
		(*(obj->wydarzenie[i])).wyswietl_dokladne();
		if ((*(obj->wydarzenie[i])).sledzenie()) {
			for (int j = 0; j < sle->sledzone.size(); j++) {
				if ((*(obj->wydarzenie[i])) == (*(sle->sledzone[j]))) {
					*sle -= j;
					f = 1;
				}
			}
			if (f == 0) {
				*sle += (*(obj->wydarzenie[i]));
			}
		}
	}
	catch (BrakException &e) {
		cout << e.komunikat();
	}
}

void Pula::oszacuj_sledzone() {
	int s_m = 0;
	int live = 0;
	int c;
	for (int i = 0; i < sle->sledzone.size(); i++) {
		c = (*(sle->sledzone[i])).get_dlugosc();
		if (c == -1)	live++;
		if (c >= 0)		s_m += c;
	}
	int h = s_m / 60;
	int m = s_m % 60;
	cout << "Szacuje, ze na obejrzenie seriali i filmow, ktore sledziesz potrzebujesz " << h << " godzin i ";
	cout << m << " minut.\nDodatkowo sledzisz " << live << "livestreamow.\n";
}

void Pula::przypomnienie() {
	for (int i = 0; i < obj->wydarzenie.size(); i++) {
		(*(obj->wydarzenie[i])).przypominaj();
	}
}

void Pula::petla() {
	oszacuj_sledzone();
	przypomnienie();
	while (true) {
		cout << "Wybierz:\n 1 - lista;\n 2 - dodaj;\n 3 - usun;\n 4 - edytuj;\n 5 - pokaz szacowany czas ogladania;\n 6 - przypomnianie o livach;\n 7 - wyjdz z aplikacji.\n";
		cin >> wybor;
		cin.clear();
		cin.ignore(1000, '\n');
		if (wybor == '7')	exit(1);
		if (wybor == '1') {
			wyswietl_liste();
			cout << "Czy chcesz zobaczyc szczegolowe informacje o wybranym programie?\nTak lub Nie\n";
			string czy_zobaczyc;
			try {
				cin >> czy_zobaczyc;
				cin.ignore(1000, '\n');
				transform(czy_zobaczyc.begin(), czy_zobaczyc.end(), czy_zobaczyc.begin(), ::tolower);
				if (czy_zobaczyc != "nie" && czy_zobaczyc != "tak")
					throw InputException("Nie odpowiedziales poprawnie na pytanie. Uznam jednak, ze nie chcesz widziec zadnych dodatkowych informacji.\n");
				if (czy_zobaczyc == "tak") {
					wyswietl_szczegolowe();
				}
			}
			catch (InputException &input) {
				string s = input.wypisz_komunikat();
				cout << s;
			}
			catch (BrakException &input) {
				cout << input.komunikat();
			}
		}
		if (wybor == '2') {
			char sfl = ' ';
			while (true) {
				cout << "Wybierz: s - serial, f - film, l - live, z - zrezygnuj.\n";
				cin >> sfl;
				cin.clear();
				cin.ignore(1000, '\n');
				sfl = tolower(sfl);
				if (sfl == 's') {
					Serial *serial = new Serial();
					*obj += *serial;
					if (serial->czy_sledzony())	*sle += *serial;
					serial->wyswietl();
					break;
				}
				if (sfl == 'l') {
					livestream *live = new livestream();
					*obj += *live;
					if (live->czy_sledzony())	*sle += *live;
					live->wyswietl();
					break;
				}
				if (sfl == 'f') {
					film * fil = new film();
					*obj += *fil;
					if (fil->czy_sledzony())	*sle += *fil;
					fil->wyswietl();
					break;
				}
				if (sfl == 'z')	break;
			}
		}
		if (wybor == '3') {
			cout << "Co chcesz usunac? Podaj tytul:\n";
			string tytul;
			getline(cin, tytul);
			try {
				int i = szukaj(tytul);
				*obj -= i;
				if ((*(obj->wydarzenie[i])).czy_sledzony())	*sle -= i;
				cout << "Usunieto!\n";
			}
			catch (BrakException &e) {
				cout << e.komunikat();
			}
		}
		if (wybor == '4') {
			cout << "Podaj nazwe programu, ktory chcesz edytowac:\n";
			string tytul;
			getline(cin, tytul);
			try {
				int i = szukaj(tytul);
				(*(obj->wydarzenie[i])).edytuj();
				(*(obj->wydarzenie[i])).wyswietl();
			}
			catch (BrakException &e) {
				cout << e.komunikat();
			}
		}
		if (wybor == '5') {
			oszacuj_sledzone();
		}
		if (wybor == '6') {
			przypomnienie();
		}
		zapisywanie_do_pliku();
	}
}


Pula::~Pula()
{
}
