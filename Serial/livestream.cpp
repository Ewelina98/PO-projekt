#include "livestream.h"

bool przestepny(int rok) {
	return (rok % 4 == 0 && rok % 100 != 0 || rok % 400 == 0);
}

int dni_w_miesiacu(int miesiac, int rok) {
	if (miesiac == 1 || miesiac == 3 || miesiac == 5 || miesiac == 7 || miesiac == 9 || miesiac == 11)
		return 31;
	if (miesiac == 2 && !(przestepny(rok)))	return 28;
	if (miesiac == 2 && przestepny(rok)) return 29;
	if (miesiac == 4 || miesiac == 6 || miesiac == 8 || miesiac == 10 || miesiac == 12)	return 30;
	return -1;
}

int livestream::wpisz_dane(int maks) {
	int i;
	cin >> i;
	while (!cin || i > maks) {
		if (!cin)	cout << "Podaj liczbe!\n";
		else if (i > maks)	cout << "Liczba musi byc mniejsza niz " << maks << endl;
		cin >> i;
	}
	return i;
}

float wpisz_dane_f() {
	float f;
	cin >> f;
	while (!cin || f > 10.0) {
		if (f > 10.0)	cout << "Liczba za duza. Od 0 do 10!\n";
		else if (!cin)	cout << "Podaj liczbe nie napis.\n";
		cin >> f;
	}
	return f;
}

livestream::livestream(){
	cout << "Podaj nazwe livu.\n";
	getline(cin, nazwa_programu);
	cout << "Podaj gatunek.\n";
	getline(cin, gatunek);
	cout << "Podaj rok wydarzenia.\n";
	rok_wydarzenia = wpisz_dane(3000);
	while (rok_wydarzenia < 1000) {
		cout << "Rok musi byc wiekszy niz rok 1000 :).\n";
		rok_wydarzenia = wpisz_dane(3000);
	}
	cout << "Podaj miesiac wydarzenia. Liczby od 1 do 12.\n";
	miesiac_wydarzenia = wpisz_dane(12);
	while (miesiac_wydarzenia < 1) {
		cout << "Miesiace liczymy od 1.\n";
		miesiac_wydarzenia = wpisz_dane(12);
	}
	cout << "Podaj dzien wydarzenia.\n";
	dzien_wydarzenia = wpisz_dane(dni_w_miesiacu(miesiac_wydarzenia, rok_wydarzenia));
	while (dzien_wydarzenia < 1) {
		cout << "Dni liczymy od 1.\n";
		dzien_wydarzenia = wpisz_dane(dni_w_miesiacu(miesiac_wydarzenia, rok_wydarzenia));
	}
	cout << "Podaj godzine:\n";
	godzina = wpisz_dane(23);
	while (godzina < 0) {
		cout << "Godziny od 0 do 23.\n";
		godzina = wpisz_dane(23);
	}
	cout << "Podaj minute wydarzenia.\n";
	minuta = wpisz_dane(59);
	while (minuta < 0) {
		cout << "Minuty od 0 do 59\n";
		minuta = wpisz_dane(59);
	}
	cout << "Na ile przewidujesz ocene tego live? W skali od 1 do 10.\n";
	ocena = wpisz_dane_f();
	while (ocena < 0.0) {
		cout << "Ocena w skali od 0 do 10\n";
		ocena = wpisz_dane_f();
	}
	cout << "Czy chcesz sledzic ten live?\n Tak lub nie.\n";
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

livestream::livestream(string nazwa, string gatune, float ocen, int dzien, int miesiac, int rok, int h, int m, bool sledz){
	nazwa_programu = nazwa;
	gatunek = gatune;
	ocena = ocen;
	dzien_wydarzenia = dzien;
	miesiac_wydarzenia = miesiac;
	rok_wydarzenia = rok;
	godzina = h;
	minuta = m;
	sledzony = sledz;
}

void livestream::ustaw_dzisiaj() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	dzisiaj_dzien = st.wDay;
	dzisiaj_miesiac = st.wMonth;
	dzisiaj_rok = st.wYear;
	a_godz = st.wHour;
	a_minuta = st.wMinute;
}

void livestream::zapisz(string t) {
	fstream plik;
	plik.open(t, ios::out | ios::app);
	plik << "l\n" << nazwa_programu << "\n" << gatunek << "\n" << ocena << "\n" << dzien_wydarzenia << "\n";
	plik << miesiac_wydarzenia << "\n" << rok_wydarzenia << "\n" << godzina << "\n" << minuta << "\n" << sledzony << "\n";
	plik.close();
}

void livestream::przypominaj() {
	ustaw_dzisiaj();
	if ((dzien_wydarzenia == dzisiaj_dzien) && (miesiac_wydarzenia == dzisiaj_miesiac) && (rok_wydarzenia == dzisiaj_rok)) {
		if ((a_godz < godzina) || ((a_godz == godzina) && (a_minuta < minuta))) {
			cout << "Dzisiaj o " << godzina << ":";
			if (minuta < 10) cout << "0" << minuta << " zaczyna sie " << nazwa_programu << " (livestream).\n";
			else cout << minuta << " zaczyna sie " << nazwa_programu << " (livestream).\n";
		}
	}
}

void livestream::wyswietl() {
	cout << setw(10) << "Live" << setw(20) << nazwa_programu << setw(15) << gatunek << setw(7) << ocena << endl;
}

void livestream::wyswietl_dokladne() {

	cout << setw(25) << "Rodzaj" << setw(2) << "||" << setw(30) << "Live" << endl;
	cout << setw(25) << "Tytul" << setw(2) << "||" << setw(30) << nazwa_programu << endl;
	cout << setw(25) << "Gatunek" << setw(2) << "||" << setw(30) << gatunek << endl;
	cout << setw(25) << "Ocena" << setw(2) << "||" << setw(30) << ocena << endl;
	cout << setw(25) << "Data" << setw(2) << "||" << setw(22);
	cout << dzien_wydarzenia << ".";
	if(miesiac_wydarzenia < 10) cout << "0" << miesiac_wydarzenia << "." << rok_wydarzenia << endl;
	else cout << miesiac_wydarzenia << "." << rok_wydarzenia << endl;
	cout << setw(25) << "Godzina" << setw(2) << "||" << setw(26);
	if(godzina < 10) cout << "0" << godzina << ":";
	else cout << godzina << ":";
	if(minuta < 10) cout << "0" << minuta << endl;
	else cout << minuta << endl;
	cout << setw(25) << "Sledzony" << setw(2) << "||" << setw(30);
	if (sledzony)	cout << "Tak" << endl;
	else cout << "Nie" << endl;
}

void livestream::edytuj() {
	string nazwa_pliku = "notepad \"tmp.txt\"";
	fstream p;
	p.open("tmp.txt", ios::out | ios::trunc);
	p << "Tytul:\n" << nazwa_programu << "\nGatunek:\n" << gatunek << "\nOcena:\n" << ocena;
	p << "\nRok:\n" << rok_wydarzenia << "\nMiesiac:\n" << miesiac_wydarzenia << "\nDzien:\n" << dzien_wydarzenia;
	p << "\nGodzina:\n" << godzina << "\nMinuta:\n" << minuta << "\n";
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
		if (s == "Rok:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		float f = (float)atof(s.c_str());
		if (!(abs(f - int(f)) >= 0))	throw LiczbaException();
		ocena = f;
		getline(p, s);
		if (s != "Rok:") throw InputException();
		getline(p, s);
		if (s == "Miesiac:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		int i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		if (i > 3000 || i < 1000)	throw LiczbaException("Nasz kalendarz obejmuje tylko lata od 1000 do 3000 roku. :)\n");
		rok_wydarzenia = i;
		getline(p, s);
		if (s != "Miesiac:") throw InputException();
		getline(p, s);
		if (s == "Dzien:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		if (i > 12)	throw LiczbaException("Mamy tylko 12 miesiecy w roku. Podales za duza liczbe.\n");
		miesiac_wydarzenia = i;
		getline(p, s);
		if (s != "Dzien:") throw InputException();
		getline(p, s);
		if (s == "Godzina:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		if (i > dni_w_miesiacu(miesiac_wydarzenia, rok_wydarzenia)) {
			throw LiczbaException("W tym miesiacu nie ma tylu dni.\n");
			dzien_wydarzenia = dni_w_miesiacu(miesiac_wydarzenia, rok_wydarzenia);
		}
		dzien_wydarzenia = i;
		getline(p, s);
		if (s != "Godzina:") throw InputException();
		getline(p, s);
		if (s == "Minuta:")	throw InputException("Usunales dane calkowicie. :( Nie mo¿emy wprowadzic takiej liczby do naszej bazy!\n");
		i = atoi(s.c_str());
		if (i == 0) throw LiczbaException();
		if (i > 23)	throw LiczbaException("Podales za duza liczbe!. Tylko od 0 do 23!\n");
		godzina = i;
		getline(p, s);
		if (s != "Minuta:")	throw InputException();
		getline(p, s);
		if (s == "")	throw InputException("Usunales dane. :( Jesli program zaczyna sie o pelnej godzinie wpisz po prostu 0");
		i = atoi(s.c_str());
		if (i == 0)	throw LiczbaException();
		if (i > 59) throw LiczbaException("Za duza liczba. Tylko od 0 do 59!\n");
		minuta = i;
	}
	catch (InputException &input) {
		string s = input.wypisz_komunikat();
		cout << s;
	}
	p.close();
}

livestream::~livestream(){

}
