#pragma once
#include <windows.h>
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <deque>
#include <algorithm>
#include "Track.h"
#include "Map.h"
#include "Color.h"
#include "MyLogger.h"
#include "Station.h"
class Route:public Track
{
public:
	struct route_point {
		int fsx, fsy, fex, fey;
		int sx, sy, ex, ey;
		int route_id;
		int station_sid, station_eid;
		std::map<int, int> front_station_type; //end 点的 前边点的类型
		std::map<int, int> back_station_type; //start 点的 后边点的类型
	};
	Route(Map*, Track*, Station*);
	std::pair<int, int> JudgeOnStation(int, int);
	bool JudgeOnEndpoint(int, int, int, int);
	void GetRouteInfo();
	void DrawRoute();
	route_point GetRouteEndpoint(int, int, int, int);
	std::vector<std::deque<route_point> > route_info;
private:
	Map* mp;
	Track* p_track;
	Station* ptr_station;

	std::mutex mu_route;
	MyLogger* myLoger = NULL;
};

