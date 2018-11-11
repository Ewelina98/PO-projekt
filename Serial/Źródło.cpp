#include <iostream>
#include "Pula.h"
#include "Lista.h"
#include "Sledzone.h"
using namespace std;

int main() {
	Lista *lista = new Lista();
	Sledzone *s = new Sledzone();
	Pula *pula = new Pula(lista, s);
	getchar();
}