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
	void GetAllTrackInfo();
	void DrawTrackSelect();
	~Track();

	int used_track;
	int owned_track;
	std::vector<int> track_color;
	std::vector<std::pair<std::pair<int, int>, int> > track_info; // center_x, center_y, r
private:
	const int track_num = 7; 
	MyLogger* myLoger = NULL;
	int x = 100 + 2048 * 25 / 64 + 70;
	int y = 344;
	bool vis[40];
};

