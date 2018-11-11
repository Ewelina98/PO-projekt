#include "film.h"

float film::wpisz_dane_f() {
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

bool truefalse() {
	string s = " ";
	while (s != "tak" && s != "nie") {
		cin >> s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (s == "tak") {
			return true;
		}
		else {
			return false;
		}
		cout << "Podaj tak lub nie!\n";
	}
}

int wpisz_dane(int min, int max) {
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

film::film() {
	cout << "Podaj nazwe filmu.\n";
	getline(cin, nazwa_programu);
	cout << "Podaj gatunek.\n";
	getline(cin, gatunek);
	cout << "Jak dlugi jest ten film. Podaj w minutach.\n";
	dlugosc = wpisz_dane(0, 1000);
	cout << "Na ile oceniasz film? W skali od 0 do 10.\n";
	ocena = wpisz_dane_f();
	cout << "Czy widziales juz ten film?\n";
	czy_obejrzany = truefalse();
	cout << "Czy chcesz sledzic ten film?\n Tak lub nie.\n";
	sledzony = truefalse();
}

film::film(string nazwa, string gat, int dl, float ocen, bool obejrzany, bool sledz) {
	nazwa_programu = nazwa;
	gatunek = gat;
	ocena = ocen;
	dlugosc = dl;
	sledzony = sledz;
	czy_obejrzany = obejrzany;
}

void film::zapisz(string t) {
	fstream plik;
	plik.open(t, ios::out | ios::app);
	plik << "f\n" << nazwa_programu << "\n" << gatunek << "\n" << dlugosc << "\n" << ocena << "\n";
	plik << czy_obejrzany << "\n" << sledzony << endl;
	plik.close();
}

void film::wyswietl() {
	cout << setw(10) << "Film" << setw(20) << nazwa_programu << setw(15) << gatunek << setw(7) << ocena << endl;
}

void film::wyswietl_dokladne() {
	cout << setw(25) << "Rodzaj" << setw(2) << "||" << setw(30) << "Film" << endl;
	cout << setw(25) << "Tytul" << setw(2) << "||" << setw(30) << nazwa_programu << endl;
	cout << setw(25) << "Gatunek" << setw(2) << "||" << setw(30) << gatunek << endl;
	cout << setw(25) << "Dlugosc w min." << setw(2) << "||" << setw(30) << dlugosc << endl;
	cout << setw(25) << "Ocena" << setw(2) << "||" << setw(30) << ocena << endl;
	cout << setw(25) << "Obejrzany" << setw(2) << "||" << setw(30);
	if (czy_obejrzany)	cout << "Tak" << endl;
	else cout << "Nie" << endl;
	cout << setw(25) << "Sledzony" << setw(2) << "||" << setw(30);
	if (sledzony)	cout << "Tak" << endl;
	else cout << "Nie" << endl;

}

int film::get_dlugosc() {
	return dlugosc;
}

void film::edytuj() {
	string nazwa_pliku = "notepad \"tmp.txt\"";
	fstream p;
	p.open("tmp.txt", ios::out | ios::trunc);
	p << "Tytul:\n" << nazwa_programu << "\nGatunek:\n" << gatunek << "\nOcena:\n" << ocena;
	p << "\nDlugosc:\n" << dlugosc << "\nCzy widziales:\n" << czy_obejrzany << endl;
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
		if (s == "Dlugosc:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		float f = (float)atof(s.c_str());
		if (!(abs(f - int(f)) >= 0))	throw LiczbaException();
		if (f > 10)	throw LiczbaException("Ocena tylko w skali od 0 do 10");
		ocena = f;
		getline(p, s);
		if (s != "Dlugosc:") throw InputException();
		getline(p, s);
		if (s == "Czy widziales:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		int i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		dlugosc = i;
		getline(p, s);
		if (s != "Czy widziales:") throw InputException();
		getline(p, s);
		if (s == "")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (!(s == "tak" || s == "nie")) throw InputException("Nie uwzgledniam takiej odpowiedzi dla pytania: Czy widziales?.\n Tylko tak lub nie. Mo¿esz sprobowac jeszcze raz.\n");
		if (s == "tak")	czy_obejrzany = true;
		if (s == "nie")	sledzony = false;
	}
	catch (InputException &input) {
		string s = input.wypisz_komunikat();
		cout << s;
	}
	p.close();
}

film::~film() {

}
