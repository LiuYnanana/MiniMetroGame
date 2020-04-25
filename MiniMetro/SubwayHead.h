#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <easyx.h>			
#include <conio.h>
#include "MyLogger.h"


class SubwayHead
{
public:
	SubwayHead();
	void DrawSubwayHead();
	~SubwayHead();
private:
	int x = 40, y = 400, r = 34;
	std::mutex mu_sub_head;
	MyLogger* myLoger = NULL;

};

