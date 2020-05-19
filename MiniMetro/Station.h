#pragma once
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "Graphics.h"
#include "MyLogger.h"
#include "Map.h"

class Station:public Map
{
public:
	Station(Map *);
	~Station();
	
	int RandPassagerTime();
	std::pair<int, int> GetPassagerOffset(int, int);
	std::vector<int> GetShapePoint(int, int, int, int);


	void DrawPassagerWarning(int);
	void CanclePassagerWarning(int);
	void GetStationPassagerInfo();
	void DrawStationPassager();
	
	void MonitorStationOvertime();

	void DrawEndPicture();
	struct passager_shape {
		int shape;
		std::vector<int> v_point;
	};

	std::vector<std::vector<passager_shape> > sta_passager_pos; //哪一个站点  八位乘客的位置
	std::mutex mu_station;
private:
	Map* ptr_map;
	
	std::vector <std::pair<int, int> > sta_overtime;

	int arrive_people;

};

