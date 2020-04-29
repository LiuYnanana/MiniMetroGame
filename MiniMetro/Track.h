#pragma once
#include <vector>
#include <time.h>
#include <iostream>
#include "Color.h"
#include "Mylogger.h"

class Track
{
public:
	Track();
	void GetAllTrackColor();
	void DrawTrackSelect();
	~Track();
private:
	std::vector<int> track_color;
	const int track_num = 7;
	MyLogger* myLoger = NULL;
	int x = 100 + 2048 * 25 / 64 + 70;
	int y = 344;
	bool vis[20];
};

