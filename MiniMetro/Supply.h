#pragma once
#include "Bridge.h"
#include "SubwayHead.h"
#include "Track.h"
#include "Clock.h"
#include "MyLogger.h"
#include "Map.h"
class Supply
{
public:
	Supply(SubwayHead*, Bridge*, Track*, Clock*, Map*);
	int GetSelectSupply(int, int);
	void DealSelectSupply();
	void DrawGovernmentSupply();
	void GetGovernmentSupply();
	~Supply();

	std::vector<std::pair<int, std::pair<int, int> > >supply_info;
private:
	SubwayHead* ptr_sub_head;
	Bridge* ptr_bridge;
	Track* ptr_track;
	Clock* ptr_clock;
	Map* ptr_map;
	MyLogger* myLoger = NULL;
};

