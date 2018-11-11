#include "Lista.h"



Lista::Lista(){
}

void Lista::operator+=(Wydarzenie &w) {
	wydarzenie.push_back(&w);
}

void Lista::operator-=(int i) {
	wydarzenie.erase(wydarzenie.begin() + i);
}

Lista::~Lista(){

}
