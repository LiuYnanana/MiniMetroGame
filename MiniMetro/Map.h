#pragma once
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <easyx.h>			
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <windows.h>
#include "File.h"
#include "graphics.h"
#include "MyLogger.h"
#include <iostream>

extern std::mutex mu_draw;
typedef std::vector<std::pair<int, int> > point_list;

class Map
{
public:
	Map();
	void GetStation(std::string);
	void GetRiver(std::string);

	void SetStationShapeNum();
	static bool cmp_distance_center(std::pair<int, int>, std::pair<int, int>);
	static bool cmp_river_x(std::pair<int, int>, std::pair<int, int>);
	int TimeInterval();
	void RemoveAdjacentPoint();

	void DrawStationShape(std::pair<int, int>);

	void DrawBackground();
	void DrawRiver(std::string);
	void DrawStation(std::string);
	void DrawMap(std::string, std::string);

	~Map();
private:
	int a1 = 25, b1 = 64, a2 = 13, b2 = 32;
	int add_left = 100, add_right = 100, add_down = 20;
	int x = 2048 * a1 / b1, y = 1536 * a2 / b2 + add_down;
	int center_x = x / 2 + add_left, center_y = y / 2;
	int num_ractangle, num_circle, num_triangle, num_fivangle, num_pentagram, num_crisscross, num_shape[10];
	static const int cx = 548;
	static const int cy = 336;
	int cnt_appear_sta = 0;
	LPCTSTR background_path = _T("background.png");
	point_list river, station;
	point_list sta_appear, sta_new_position, sta_wait, sta_old_position;
	point_list riv_move, riv_old_position, riv_new_position;
	std::map<int, bool> vis_station, vis_river, vis_station_shape;
	std::vector<int> v_station_shape;
	MyLogger* myLoger = NULL;
};



