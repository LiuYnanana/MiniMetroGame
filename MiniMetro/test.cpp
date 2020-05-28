#include <iostream>
#include <fstream>
#include <cassert>
#include <thread>
#include <mutex>
#include <exception>
#include "Map.h"
#include "File.h"
#include "Clock.h"
#include "Bridge.h"
#include "SubwayHead.h"
#include "MyLogger.h"
#include "Track.h"
#include "Station.h"
#include "Route.h"
#include "MapInterface.h"
#include "MapData.h"
#include "Supply.h"

std::mutex mu_draw;  

int main()
{

	//freopen("log.txt", "w", stdout);
	//try {

	MyLogger* myLoger;
	myLoger = MyLogger::GetInstance();


	Map map("E:\\MiniMetro\\getMap\\river.txt", "E:\\MiniMetro\\getMap\\station.txt");
	Map* p_map = &map;
	map.DrawBackground();

	Clock clock;
	Clock* p_clock = &clock;

	Bridge bridge;
	Bridge* p_bridge = &bridge;

	Track track;
	Track* p_track = &track;

	Station station(p_map);
	Station* p_station = &station;

	Route route(p_map, p_track, p_station, p_bridge);
	Route* p_route = &route;

	SubwayHead subway_head(p_route, p_station, p_track, p_map);
	SubwayHead* p_sub_head = &subway_head;

	Supply supply(p_sub_head, p_bridge, p_track, p_clock);
	Supply* p_supply = &supply;

	MapData mapData(p_map, p_clock, p_sub_head, p_bridge, p_track, p_station, p_route, p_supply);
	mapData.InitMap();
	std::thread th_getData(&MapData::GetDrawMapData, &mapData);
	

	MapInterface mpInface(p_map, p_clock, p_sub_head, p_bridge, p_track, p_station, p_route, p_supply);
	std::thread th_draw(&MapInterface::ShowMapInterface, &mpInface);


	th_draw.join();
	//th_getData.join();

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����

	/*

	

	
	//subway_head.DrawSubwayHead();


	//bridge.DrawBridge();


	//track.DrawTrackSelect();

	
	Route route(p_map);

*/

	//-------------------------------------------------------

	//std::thread th_station(&Map::DrawStation, &map, "E:\\MiniMetro\\getMap\\station.txt");

	//Sleep(1000);
	//std::thread th_t(&Station::DrawStationPassager, &station);
	//std::thread th_monitor_overtime(&Station::MonitorStationOvertime, &station);

	//std::thread th_route(&Route::DrawRoute, &route);

	//Sleep(1000);
	//std::thread th_clock(&Clock::DrawClockPointer, &clock);

	//th_clock.join();
	//th_station.join();
	//th_t.join();

	/*}
	catch (const char* str_err) {
		std::cout << str_err << std::endl;
	}*/

	
	

}


