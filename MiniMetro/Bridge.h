#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>

extern std::mutex mu_draw;

class Bridge	
{
public:
	Bridge();
	void DrawBridge();
	~Bridge();
private:
	int x = 40, y = 480, r = 34;
	std::mutex mu_bridge;
};

