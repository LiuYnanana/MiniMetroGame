#pragma once
#include "City.h"
#include <easyx.h>
#include <conio.h>
#include <string>
extern bool end;
class City
{
public:
	City();
	void DrawCity();
	std::string SelectCity();
	~City();
};

