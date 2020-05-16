#pragma once
#include "Map.h"
#include "Clock.h"
#include "Bridge.h"
#include "SubwayHead.h"
#include "Track.h"
#include "Station.h"
#include "Route.h"
#include <thread>
class MapData
{
public:
	MapData(Map*, Clock*, SubwayHead*, Bridge*, Track*, Station*, Route*);
	void InitMap();
	void GetDrawMapData();
private:
	Map* ptr_map;
	Clock* ptr_clock;
	SubwayHead* ptr_sub_head;
	Bridge* ptr_bridge;
	Track* ptr_track;
	Station* ptr_station;
	Route* ptr_route;
};

