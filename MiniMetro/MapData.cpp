#include "MapData.h"

MapData::MapData(Map* _map, Clock* _clock, SubwayHead* _subwayHead, Bridge* _bridge,
	Track* _track, Station* _station, Route* _route) {
	ptr_map = _map;
	ptr_clock = _clock;
	ptr_sub_head = _subwayHead;
	ptr_bridge = _bridge;
	ptr_track = _track;
	ptr_station = _station;
	ptr_route = _route;
}

void MapData::InitMap() {
	ptr_map->GetRiver();
	ptr_map->GetStation();

	ptr_track->GetAllTrackInfo();
}

void MapData::GetDrawMapData() {
	std::thread th1(&Map::GetStationInfo, ptr_map);
	std::thread th2(&Station::GetStationPassagerInfo, ptr_station);
	std::thread th3(&Route::GetRouteInfo, ptr_route);
	std::thread th4(&SubwayHead::GetSubwayHeadInfo, ptr_sub_head);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}