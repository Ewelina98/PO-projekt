#include "InputException.h"



InputException::InputException(){
	
}

InputException::InputException(string s) {
	wiadomosc = s;
}

string InputException::wypisz_komunikat() {
	return wiadomosc;
}

InputException::~InputException(){

}
