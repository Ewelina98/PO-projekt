#include "Wydarzenie.h"
#include "iostream"
#include <string>
#include "fstream"

Wydarzenie::Wydarzenie() {

}

bool Wydarzenie::operator==(string t) {
	if (nazwa_programu == t)	return true;
	return false;
}

void Wydarzenie::wyswietl() {
	cout << setw(10) << "Brak" << setw(20) << nazwa_programu << setw(15) << gatunek << setw(7) << ocena << endl;
}

void Wydarzenie::wyswietl_dokladne() {
	cout << setw(15) << "Rodzaj" << setw(2) << "||" << setw(20) << "Brak" << endl;
	cout << setw(15) << "Tytul" << setw(2) << "||" <<  setw(20) << nazwa_programu << endl;
	cout << setw(15) << "Gatunek" << setw(2) << "||" << setw(20) << gatunek << endl;
	cout << setw(15) << "Ocena" << setw(2) << "||" << setw(20) << ocena << endl;
	cout << setw(15) << "Sledzony" << setw(2) << "||" << setw(20);
	if (sledzony)	cout << "Tak" << endl;
	else cout << "Nie" << endl;
}

void Wydarzenie::edytuj() {
	string nazwa_pliku = "notepad \"tmp.txt\"";
	fstream p;
	p.open("tmp.txt", ios::out | ios::trunc);
	p << "Tytu³: " << nazwa_programu << "\nGatunek: " << gatunek << "\nOcena: " << ocena << "\n";
	p.close();
	system(nazwa_pliku.c_str());
	p.open("tmp.txt", ios::in);
	string s;
	p >> s >> nazwa_programu >> s >> gatunek >> s >> ocena;
	p.close();
}

bool Wydarzenie::sledzenie() {
	if (sledzony == true) {
		cout << "Sledzisz juz ten program. Chcesz zrezygnowac? Tak lub nie.\n";
		string t;
		getline(cin, t);
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (t != "nie" && t != "tak")
			throw InputException("Nie odpowiedziales poprawnie na pytanie. Uznam jednak, ze nie chcesz widziec zadnych dodatkowych informacji.\n");
		if (t == "tak") {
			sledzony = false;
			return true;
		}
		return false;
	}
	else {
		cout << "Nie sledzisz tego programu. Chcesz zaczac od teraz? Tak lub nie.\n";
		string t;
		getline(cin, t);
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (t != "nie" && t != "tak")
			throw InputException("Nie odpowiedziales poprawnie na pytanie. Uznam jednak, ze nie chcesz widziec zadnych dodatkowych informacji.\n");
		if (t == "tak") {
			sledzony = true;
			return true;
		}
		return false;
	}
}

void Wydarzenie::zapisz(string f) {
	fstream plik;
	plik.open(f, ios::out | ios::app);
	plik << "w\n" << nazwa_programu << "\n" << gatunek << "\n" << ocena << "\n" << sledzony << endl;
	plik.close();
}

bool Wydarzenie::czy_sledzony() {
	return sledzony;
}

void Wydarzenie::przypominaj() {
	
}

int Wydarzenie::get_dlugosc() {
	return -2;
}

bool Wydarzenie::operator == (Wydarzenie &w) {
	if (nazwa_programu == w.nazwa_programu)	return true;
	return false;
}

Wydarzenie::~Wydarzenie() {

}

