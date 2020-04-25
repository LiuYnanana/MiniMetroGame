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

std::mutex mu_draw;

int main()
{
	//freopen("log.txt", "w", stdout);
	

	//try {

	Map map;
	map.DrawMap("E:\\MiniMetro\\getMap\\river.txt", "E:\\MiniMetro\\getMap\\station.txt");

	SubwayHead subway_head;
	subway_head.DrawSubwayHead();

	Bridge bridge;
	bridge.DrawBridge();

	std::thread th_station(&Map::DrawStation, &map, "E:\\MiniMetro\\getMap\\station.txt");
	Sleep(1000);
	Clock clock;
	std::thread th_clock(&Clock::DrawClockPointer, &clock);

	th_clock.join();
	th_station.join();

	/*}
	catch (const char* str_err) {
		std::cout << str_err << std::endl;
	}*/



	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口


}



