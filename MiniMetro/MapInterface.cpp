#include "MapInterface.h"

MapInterface::MapInterface(Map* _map, Clock* _clock, SubwayHead* _subwayHead, Bridge* _bridge, 
	Track* _track, Station* _station, Route* _route, Supply* _supply) {
	ptr_map = _map;
	ptr_clock = _clock;
	ptr_sub_head = _subwayHead;
	ptr_bridge = _bridge;
	ptr_track = _track;
	ptr_station = _station;
	ptr_route = _route;
	ptr_supply = _supply;
	myLoger = MyLogger::GetInstance();
}

void MapInterface::ShowMapInterface() {
	
	BeginBatchDraw();

	int clock_point = 0;
	while (true) {
		ptr_clock->DrawClockPointer(clock_point++);

		if (ptr_clock->week) {
			//std::thread t_supply(&Supply::DrawGovernmentSupply, ptr_supply);
			ptr_supply->DrawGovernmentSupply();
			//t_supply.join();
			ptr_clock->week = false;
			cleardevice();
		}
		ptr_map->DrawRiver();
		ptr_sub_head->DrawSubwayHead();
		ptr_bridge->DrawBridge();
		ptr_track->DrawTrackSelect();
	
		ptr_map->DrawStation();
		ptr_station->DrawStationPassager();

		ptr_route->DrawRoute();
		ptr_sub_head->DrawSubwayHeadMove();
		ptr_station->DrawStationPassager();
		ptr_station->DrawPassagerWarning();
		FlushBatchDraw();
		Sleep(100);
		cleardevice();
		if (end) {
			std::cout << end << std::endl;
			break;
		}
		std::cout << "while" << std::endl;
	}
	std::cout << "interface!" << std::endl;
	EndBatchDraw();
	

	std::cout << "interface!!" << std::endl;
}