#pragma once
#include "InputException.h"
using namespace std;
class LiczbaException :
	public InputException
{
public:
	LiczbaException();
	LiczbaException(string s);
	~LiczbaException();
};

