#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <easyx.h>			
#include <conio.h>
#include <iostream>
#include "MyLogger.h"
#include "Route.h"
#include "Station.h"
#include "Graphics.h"
#include "Track.h"
#include "MyDeque.h"

class SubwayHead
{
public:
	SubwayHead(Route*, Station*, Track*, Map* );
	void DrawSubwayHead();
	std::pair<int, int> GetPassagerPos(int);
	std::vector<int> GetShapePoint(int, int, int, int);
	std::pair<int, int> GetNewPos(int, int, int, int, int);
	void GetSubwayHeadInfo();
	void DrawSubwayHeadMove();
	~SubwayHead();

	struct subHead {
		int subHead_size;
		int subHead_num;
		int pos_x, pos_y;
		int route_id, station_id;
		int director;
		bool sta_left, sta_right;
		bool wait_pos;
		std::map<int, int> front_station_type; //end 点的 前边点的类型
		std::map<int, int> back_station_type; //start 点的 后边点的类型
	};
	std::vector<subHead> subHead_info;

	struct position {
		int sx, sy;
		int ex, ey;
		int x, y;
		bool wait_pos;
	};
private:
	int x = 40, y = 400, r = 34;
	std::mutex mu_sub_head;
	MyLogger* myLoger = NULL;
	int owned_subwayHead, used_subwayHead;
	Route* ptr_route;
	Station* ptr_station;
	Track* ptr_track;
	Map* ptr_map;
	
	std::vector<MyDeque> pos_info;
	std::vector<std::pair<int, bool> > sub_now_pos;
	std::vector<std::vector<int> >passager_shape;
};

