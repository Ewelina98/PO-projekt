#pragma once
#include "string"
using namespace std;
class BrakException
{
private:
	string wiadomosc = "Nie mamy takiego tytulu w bazie!\n";
public:
	BrakException();
	string komunikat();
	~BrakException();
};

