#include "Sledzone.h"



Sledzone::Sledzone(){

}

void Sledzone::operator+=(Wydarzenie &w) {
	sledzone.push_back(&w);
}

void Sledzone::operator-=(int i) {
	sledzone.erase(sledzone.begin() + i);
}

Sledzone::~Sledzone(){

}
