#include "Serial.h"
#include "Pula.h"
#include "fstream"
using namespace std;

int Serial::wpisz_dane(int min, int max) {
	int i;
	cin >> i;
	while (!cin || i < min || i > max) {
		if (!cin)	cout << "Podaj liczbe nie tekst.\n";
		if (i < min)	cout << "Liczba musi byc wieksza od " << min << ".\n";
		if (i > max)	cout << "Liczba musi byc mniejsza od " << max << ".\n";
		cin >> i;
	}
	return i;
}

float Serial::wpisz_dane_f() {
	float i;
	cin >> i;
	while (!cin || i < 0 || i > 10.0) {
		if (!cin)	cout << "Podaj liczbe nie tekst.\n";
		if (i < 0)	cout << "Liczba musi byc wieksza od " << 0 << ".\n";
		if (i > 10)	cout << "Liczba musi byc mniejsza od " << 10 << ".\n";
		cin >> i;
	}
	return i;
}

Serial::Serial() {
	cout << "Podaj nazwe serialu.\n";
	getline(cin, nazwa_programu);
	cout << "Podaj gatunek.\n";
	getline(cin, gatunek);
	cout << "Ile sezonow ma ten serial?\n";
	liczba_sezonow = wpisz_dane(0, 1000);
	cout << "Ile odcinkow ma sezon?\n";
	liczba_odcinkow = wpisz_dane(0,1000);
	cout << "Ile odcinkow juz widziales?\n";
	liczba_obejrzanych_odcinkow = wpisz_dane(0, liczba_odcinkow);
	cout << "Jaka dl. ma jeden odcinek w minutach?\n";
	srednia_dl_odc = wpisz_dane(0, 1000);
	cout << "Na ile oceniasz serial? W skali od 1 do 10.\n";
	ocena = wpisz_dane_f();
	cout << "Czy chcesz sledzic ten serial?\n Tak lub nie.\n";
	string s = " ";
	while (s != "tak" && s != "nie") {
		cin >> s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (s == "tak") {
			sledzony = true; break;
		}
		else {
			sledzony = false; break;
		}
		cout << "Podaj tak lub nie!\n";
	}
}

Serial::Serial(string nazwa, string gatune, int l_s, int l_odc, int l_obej, int s_d_o, float ocen, bool s) {
	liczba_obejrzanych_odcinkow = l_obej;
	liczba_odcinkow = l_odc;
	nazwa_programu = nazwa;
	gatunek = gatune;
	liczba_sezonow = l_s;
	srednia_dl_odc = s_d_o;
	ocena = ocen;
	sledzony = s;
}


void Serial::wyswietl() {
	cout << setw(10) << "Serial" << setw(20) << nazwa_programu << setw(15) << gatunek << setw(7) << ocena << endl;
}

void Serial::wyswietl_dokladne() {
	cout << setw(25) << "Rodzaj" << setw(2) << "||" << setw(30) << "Serial" << endl;
	cout << setw(25) << "Tytul" << setw(2) << "||" << setw(30) << nazwa_programu << endl;
	cout << setw(25) << "Gatunek" << setw(2) << "||" << setw(30) << gatunek << endl;
	cout << setw(25) << "Ocena" << setw(2) << "||" << setw(30) << ocena << endl;
	cout << setw(25) << "Liczba sezonow" << setw(2) << "||" << setw(30) << liczba_sezonow << endl;
	cout << setw(25) << "Liczba odc. w sezonie" << setw(2) << "||" << setw(30) << liczba_odcinkow << endl;
	cout << setw(25) << "Obejrzane odc." << setw(2) << "||" << setw(30) << liczba_obejrzanych_odcinkow << endl;
	cout << setw(25) << "Srednia dl. odcinka" << setw(2) << "||" << setw(30) << srednia_dl_odc << endl;
	cout << setw(25) << "Sledzony" << setw(2) << "||" << setw(30);
	if (sledzony)	cout << "Tak" << endl;
	else cout << "Nie" << endl;
}

void Serial::edytuj() {
	string nazwa_pliku = "notepad \"tmp.txt\"";
	fstream p;
	p.open("tmp.txt", ios::out | ios::trunc);
	p << "Tytul:\n" << nazwa_programu << "\nGatunek:\n" << gatunek << "\nOcena:\n" << ocena << "\nLiczba sezonow:\n" << liczba_sezonow;
	p << "\nLiczba odc. w sezonie:\n" << liczba_odcinkow << "\nObejrzane:\n" << liczba_obejrzanych_odcinkow;
	p << "\nSrednia dl. odc.:\n" << srednia_dl_odc << "\n";
	p.close();
	system(nazwa_pliku.c_str());
	p.open("tmp.txt", ios::in);
	string s;
	try {
		getline(p, s);
		if (s != "Tytul:")	throw InputException("");
		getline(p, s);
		if (s == "Gatunek:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej nazwy do naszej bazy!\n");
		nazwa_programu = s;
		getline(p, s);
		if (s != "Gatunek:")	throw InputException();
		getline(p, s);
		if (s == "Ocena:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej nazwy do naszej bazy!\n");
		gatunek = s;
		getline(p, s);
		if (s != "Ocena:")	throw InputException();
		getline(p, s);
		if (s == "Liczba sezonow:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		float f = (float)atof(s.c_str());
		if (!(abs(f - int(f)) >= 0))	throw LiczbaException();
		ocena = f;
		getline(p, s);
		if (s != "Liczba sezonow:") throw InputException();
		getline(p, s);
		if (s == "Liczba odc. w sezonie:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		int i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		liczba_sezonow = i;
		getline(p, s);
		if (s != "Liczba odc. w sezonie:") throw InputException();
		getline(p, s);
		if (s == "Obejrzane:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		liczba_odcinkow = i;
		getline(p, s);
		if (s != "Obejrzane:") throw InputException();
		getline(p, s);
		if (s == "Srednia dl. odc.:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		liczba_obejrzanych_odcinkow = i;
		getline(p, s);
		if (s != "Srednia dl. odc.:") throw InputException();
		getline(p, s);
		if (s == "")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		srednia_dl_odc = i;
	}
	catch (InputException &input) {
		string s = input.wypisz_komunikat();
		cout << s;
	}
	p.close();
}

void Serial::zapisz(string f) {
	fstream plik;
	plik.open(f, ios::out | ios::app);
	plik << "s\n" << nazwa_programu << "\n" << gatunek << "\n" << liczba_sezonow << "\n";
	plik << liczba_odcinkow << "\n" << liczba_obejrzanych_odcinkow << "\n";
	plik << srednia_dl_odc << "\n" << ocena << "\n" << sledzony << endl;
	plik.close();
}

int Serial::get_dlugosc() {
	return srednia_dl_odc;
}

Serial::~Serial() {

}
