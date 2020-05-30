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
#include "Bridge.h"

class Route:public Track
{
public:
	struct route_point {
		int fsx, fsy, fex, fey;
		int sx, sy, ex, ey;
		int route_id;
		int station_sid, station_eid;
	};

	Route(Map*, Track*, Station*, Bridge*);
	std::pair<int, int> JudgeOnStation(int, int);
	bool JudgeOnEndpoint(int, int, int, int);

	void UpdateTrackInfo();
	int GetStationId(int, int);
	bool JudgeCircle(int, int, int, int, int, int, double);
	bool JudgeOnRiver(int, int, int, int);
	void GetRouteStationInfo(int, int, int, int, route_point&, int);
	void ConnectStationToStation(int, int, int, int);
	void ConnectStationToRoute(int, int, int, int, int);
	void ConnectRouteToStation(int, int, int, int, int);
	
	void StationDFS(int, int, int, int, bool, bool);
	void GetConnectionInfo();
	void GetRouteInfo();
	void DrawRoute();
	route_point GetRouteEndpoint(int, int, int, int);
	std::vector<std::deque<route_point> > route_info;

	int Next_station[10][100][2]; // route_id staton_id 0 1(Õý
	std::map<int, int> station_arrive[100][10][2]; // station_id route_id 0 1(
private:
	Map* mp;
	Track* p_track;
	Station* ptr_station;
	Bridge* ptr_bridge;
	
	std::mutex mu_route;
	std::mutex mu_push_sta_id;
	MyLogger* myLoger = NULL;

	int dfs_vis[100];
	int Edge_route[10][100][100]; // route_id  station station
	
	int sta_to_sta = 1;
	int sta_to_route = 2;
	int route_to_sta = 3;
	
	std::vector<int> connect_sta_id;
};

