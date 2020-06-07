#include "MapData.h"

MapData::MapData(Map* _map, Clock* _clock, SubwayHead* _subwayHead, Bridge* _bridge,
	Track* _track, Station* _station, Route* _route, Supply* _supply, Mouse* _mouse) {
	ptr_map = _map;
	ptr_clock = _clock;
	ptr_sub_head = _subwayHead;
	ptr_bridge = _bridge;
	ptr_track = _track;
	ptr_station = _station;
	ptr_route = _route;
	ptr_supply = _supply;
	ptr_mouse = _mouse;
}

void MapData::InitMap() {
	ptr_map->GetRiver();
	ptr_map->GetStation();
	ptr_track->GetAllTrackInfo();
}

void MapData::GetDrawMapData() {
	std::thread th1(&Map::GetStationInfo, ptr_map);
	std::thread th2(&Station::GetStationPassagerInfo, ptr_station);
	std::thread th3(&Mouse::MonitorMouse, ptr_mouse);
	std::thread th4(&SubwayHead::GetSubwayHeadInfo, ptr_sub_head);
	std::thread th5(&Station::MonitorStationOvertime, ptr_station);
	th1.join();
	std::cout << "1" << std::endl;
	th2.join();
	std::cout << "2" << std::endl;
	th3.join();
	std::cout << "3" << std::endl;
	th4.join();
	std::cout << "4" << std::endl;
	th5.join();
	std::cout << "5" << std::endl;
}