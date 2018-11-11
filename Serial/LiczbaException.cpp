#include "LiczbaException.h"



LiczbaException::LiczbaException(){
	wiadomosc = "Powinienes podac nam liczbe, a tego nie zrobiles!\n";
}

LiczbaException::LiczbaException(string s) {
	wiadomosc = s;
}

LiczbaException::~LiczbaException(){

}
