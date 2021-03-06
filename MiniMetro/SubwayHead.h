#pragma once
#include <iostream>
#include <mutex>
#include <graphics.h>
#include <easyx.h>			
#include <conio.h>
#include <iostream>
#include "MyLogger.h"
#include "Route.h"
#include "Station.h"
#include "Graphics.h"
#include "Track.h"
#include "MyDeque.h"
#include <mutex>
extern bool end;
class SubwayHead
{
public:
	struct subHead {
		int subHead_size;
		int subHead_num;
		int pos_x, pos_y;
		int route_id, station_id;
		int director;
		bool sta_left, sta_right;
		bool wait_pos;
	};
	std::vector<subHead> subHead_info[10];

	SubwayHead(Route*, Station*, Track*, Map*);
	void GetSubwayHeadNum();
	void GetSubwaySelect();

	void DrawNoSubwayHead();
	void DrawOneSubwayHead(int, int);
	void DrawSubwayHead();
	void DrawSubwaySelect();
	
	void GetSelectInfo(MOUSEMSG);
	std::pair<int, int> GetPassagerPos(int);
	std::vector<int> GetShapePoint(int, int, int, int);
	std::pair<int, int> GetNewPos(int, int, int, int, int);

	bool JudgeOnSubPic(int, int);
	bool JudgeCloseSubPic(int, int);

	bool JudgeRouteChange(int);
	void PushStationToBack(int);
	void PushStationToFront(int);
	void GetSubHeadPos(subHead&, int, int);
	void DealPassagers(subHead&, int, int);
	void GetSubwayHeadInfo();
	void DrawSubwayHeadMove();
	~SubwayHead();

	struct position {
		int sx, sy;
		int ex, ey;
		int x, y;
		bool wait_pos;
	};
	std::vector<std::pair<int, int> > head_num_info;


	int owned_sub_head;
	int used_sub_head;
	int sub_hold_passager;
	bool have_sub_head;
	bool select_sub;
	std::vector<std::pair<int, int> > select_subway;

	int people;
private:
	int  r = 34;
	std::mutex mu_sub_head;
	MyLogger* myLoger = NULL;
	Route* ptr_route;
	Station* ptr_station;
	Track* ptr_track;
	Map* ptr_map;
	int vis[10][5000];
	int subHead_num[10];

	std::vector<MyDeque> pos_info;
	std::vector<std::pair<int, bool> > sub_now_pos[10];
	std::vector<std::vector<int> >passager_shape[10];
};

