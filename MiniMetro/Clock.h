#pragma once
#include <mutex>
#include <iostream>
#include <easyx.h>			
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <easyx.h>
#include "MyLogger.h"

#define PI acos(-1)
extern std::mutex mu_draw;
extern bool end;
class Clock
{
public:
	Clock();
	void DrawDate(bool);
	void DrawClockBackground(int);
	void DrawClockScale();
	void DrawClockPointer(int);
	void CancleClockPointer(int);
	~Clock();
	int days = 0;
	bool week;
private:
	int x = 100 + 2048 * 25 / 64 + 70;
	int y = 70;
	int r = 28;

	std::mutex mu;
	MyLogger* myLoger = NULL;

};

