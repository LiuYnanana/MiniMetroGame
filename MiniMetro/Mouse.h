#pragma once
#include <easyx.h>
#include <conio.h>
#include <Windows.h>
#include "Route.h"
#include "SubwayHead.h"
#include "Supply.h"
#include "Rank.h"
#include "Map.h"
extern bool end;
class Mouse
{
public:
	Mouse(Map*, Route*, SubwayHead*, Supply*);
	bool JudgeExit(MOUSEMSG);
	void MonitorMouse();
	~Mouse();
private:
	Map* ptr_map;
	Route* ptr_route;
	SubwayHead* ptr_subway;
	Supply* ptr_supply;
};

