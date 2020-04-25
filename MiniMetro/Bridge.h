#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include "MyLogger.h"

class Bridge	
{
public:
	Bridge();
	void DrawBridge();
	~Bridge();
private:
	int x = 40, y = 480, r = 34;
	MyLogger* myLoger = NULL;
};

