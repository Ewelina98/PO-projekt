#pragma once
#include <string>
using namespace std;

class InputException
{
protected:
	string wiadomosc = "Zmieniles nam w pliku rzeczy, ktorych nie powinenes ruszac. :(\nSprobuj jeszcze raz, ale pamietaj, ze zmieniasz tylko wyrazy po tym znaku \":\"";
public:
	InputException();
	InputException(string s);
	virtual string wypisz_komunikat();
	~InputException();
};

