#pragma once
#include <windows.h>
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <deque>
#include "Track.h"
#include "Map.h"
#include "Color.h"
#include "MyLogger.h"
class Route:public Track
{
public:
	struct route_point {
		int fsx, fsy, fex, fey;
		int sx, sy, ex, ey;
		int route_id;
	};
	Route(Map*, Track*);
	std::pair<int, int> JudgeOnStation(int, int);
	bool JudgeOnEndpoint(int, int, int, int);
	void GetRouteInfo();
	void DrawRoute();
	route_point GetRouteEndpoint(int, int, int, int);
private:
	Map* mp;
	Track* p_track;
	std::vector<std::deque<route_point> > route_info;
	std::mutex mu_route;
	MyLogger* myLoger = NULL;
};

