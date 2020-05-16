#pragma once
#include "Clock.h"
#include "Map.h"
#include "SubwayHead.h"
#include "Bridge.h"
#include "Route.h"
#include "Station.h"
#include "MyLogger.h"
class MapInterface
{
public:
	MapInterface(Map*, Clock*, SubwayHead*, Bridge*, Track*, Station*, Route*);
	void ShowMapInterface();
private:
	Map* ptr_map;
	Clock* ptr_clock;
	SubwayHead* ptr_sub_head;
	Bridge* ptr_bridge;
	Track* ptr_track;
	Station* ptr_station;
	Route* ptr_route;
	MyLogger* myLoger = NULL;
};

