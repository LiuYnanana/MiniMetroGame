#pragma once
#include <easyx.h>
#include <conio.h>
#include <string>
extern bool end;
class City
{
public:
	City();
	void DrawRankCity();
	void DrawEasyCity();
	void DrawMidCity();
	void DrawHardCity();
	std::string SelectRankCity();
	std::string SelectEasyCity();
	std::string SelectMidCity();
	std::string SelectHardCity();
	~City();
};

