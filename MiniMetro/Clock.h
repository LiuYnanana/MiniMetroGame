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

class Clock
{
public:
	Clock();
	void DrawDate(bool);
	void DrawClockBackground();
	void DrawClockScale();
	void DrawClockPointer(int);
	void CancleClockPointer(int);
	~Clock();
private:
	int x = 100 + 2048 * 25 / 64 + 70;
	int y = 70;
	int r = 28;
	int days = 0;
	std::mutex mu;
	MyLogger* myLoger = NULL;

};

