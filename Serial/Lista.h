#pragma once
#include "vector"
#include "Wydarzenie.h"
#include "BrakException.h"
#include "Sledzone.h"
class Lista {
public:
	vector <Wydarzenie*> wydarzenie;
	Lista();
	void operator +=(Wydarzenie &w);
	void operator -=(int t);
	~Lista();
};

