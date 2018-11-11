#pragma once
#include "vector"
#include "Wydarzenie.h"
#include "BrakException.h"
class Sledzone
{
public:
	vector <Wydarzenie*> sledzone;
	Sledzone();
	void operator +=(Wydarzenie &w);
	void operator -=(int i);
	~Sledzone();
};

