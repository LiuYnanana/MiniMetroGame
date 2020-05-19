#include "MapInterface.h"

MapInterface::MapInterface(Map* _map, Clock* _clock, SubwayHead* _subwayHead, Bridge* _bridge, 
	Track* _track, Station* _station, Route* _route) {
	ptr_map = _map;
	ptr_clock = _clock;
	ptr_sub_head = _subwayHead;
	ptr_bridge = _bridge;
	ptr_track = _track;
	ptr_station = _station;
	ptr_route = _route;
	myLoger = MyLogger::GetInstance();
}

void MapInterface::ShowMapInterface() {
	
	//ptr_map->DrawBackground();
	//Sleep(1000);
	BeginBatchDraw();

	//Sleep(1000);
	int clock_point = 1;
	while (true) {

		ptr_map->DrawRiver();
		ptr_clock->DrawClockPointer(clock_point++);
		ptr_sub_head->DrawSubwayHead();
		ptr_bridge->DrawBridge();
		ptr_track->DrawTrackSelect();
	
		ptr_map->DrawStation();
		ptr_station->DrawStationPassager();

		ptr_route->DrawRoute();
		ptr_sub_head->DrawSubwayHeadMove();
		ptr_map->DrawStation();

		LOG4CPLUS_INFO(myLoger->rootLog, "All draw waiting");
		FlushBatchDraw();
		LOG4CPLUS_INFO(myLoger->rootLog, "All draw finish");
		Sleep(100);
		cleardevice();
	}

	EndBatchDraw();

//	setlinecolor(RED);
//	line(100, 200, 500, 200);
}