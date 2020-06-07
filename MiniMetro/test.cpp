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
#include "Mouse.h"
#include "StartGame.h"
#include "City.h"
std::mutex mu_draw;  
bool end;

void init() {
	std::cout << "start" << std::endl;
	initgraph(1000, 644);	// 创建绘图窗口，大小为 640x480 像素
	setbkcolor(RGB(245, 243, 239));
	cleardevice();

	StartGame start_game;
	StartGame* p_start_game = &start_game;

	City city;
	City* p_city = &city;

	p_start_game->DrawStartGame();
	bool start = p_start_game->GetSelectGame();
	std::string select_city;
	cleardevice();
	p_city->DrawCity();
	select_city = p_city->SelectCity();
	cleardevice();
	if (!start) {
		Rank rank;
		rank.GetRank(select_city + "_rank");
		rank.DrawRank();
		rank.ExitRank();
	}
	else {
		MyLogger* myLoger;
		myLoger = MyLogger::GetInstance();

		std::string river_file_name = "E:\\MiniMetro\\getMap\\" + select_city + "river.txt";
		std::string station_file_name = "E:\\MiniMetro\\getMap\\" + select_city + "station.txt";

		Map map(river_file_name, station_file_name, select_city);
		Map* p_map = &map;
		//map.DrawBackground();

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

		Supply supply(p_sub_head, p_bridge, p_track, p_clock, p_map);
		Supply* p_supply = &supply;

		Mouse mouse(p_map, p_route, p_sub_head, p_supply);
		Mouse* p_mouse = &mouse;

		MapData mapData(p_map, p_clock, p_sub_head, p_bridge, p_track, p_station, p_route, p_supply, p_mouse);
		mapData.InitMap();
		std::thread th_getData(&MapData::GetDrawMapData, &mapData);


		MapInterface mpInface(p_map, p_clock, p_sub_head, p_bridge, p_track, p_station, p_route, p_supply);
		std::thread th_draw(&MapInterface::ShowMapInterface, &mpInface);

		std::cout << "end init" << std::endl;
		th_draw.join();
		std::cout << "end init !!" << std::endl;
		th_getData.join();
		//return;
	}
}
int main()
{
	freopen("out.txt", "w", stdout);
	end = true;
	//init();

	while (true) {
		if (end) {
			end = false;
			init();
			std::cout << "end" << std::endl;
		}
	}
	
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
}


