#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <vector>
#include "MyLogger.h"

class Bridge	
{
public:
	Bridge();
	void GetBridgeInfo();
	void DrawNoBridge();
	void DrawOneBridge(int, int);
	void DrawBridge();
	~Bridge();

	int owned_bridge, used_bridge;
	bool have_bridge;
	std::vector<std::pair<int, int> >bridge_info;
private:
	int  r = 34;
	MyLogger* myLoger = NULL;
};

