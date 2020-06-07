#pragma once
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include "Graphics.h"
#include "MyLogger.h"
#include "Map.h"
extern bool end;
class Station:public Map
{
public:
	Station(Map *);
	~Station();
	
	int RandPassagerTime();
	std::pair<int, int> GetPassagerOffset(int, int);
	std::vector<int> GetShapePoint(int, int, int, int);

	void GetWarningInfo(int, int);
	void DrawPassagerWarning();
	void CanclePassagerWarning(int);
	void GetStationPassagerInfo();
	void DrawStationPassager();
	
	void MonitorStationOvertime();

	void DrawEndPicture();

	std::vector<std::vector<int> > sta_passager_pos; //哪一个站点 每位乘客
	std::mutex mu_station, mu_warning;

	struct warn_line {
		int sx, sy;
		int ex, ey;
	};
	std::vector<warn_line> warnning[100];
	bool gameover;
private:
	Map* ptr_map;
	
	std::vector <std::pair<int, int> > sta_overtime;

	int arrive_people;

};

