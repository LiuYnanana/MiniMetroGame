#pragma once
#include <iostream>
#include <map>
extern bool end;
class MyDeque
{
public:
	struct position {
		int sx, sy;
		int ex, ey;
		int x, y;
		bool wait_pos;
		bool sta_left, sta_right;
		int station_id;
    //	std::map<int, int> front_station_type; //end ��� ǰ�ߵ������
	//	std::map<int, int> back_station_type; //start ��� ��ߵ������
	};

	position& operator [] (int);
	MyDeque();
	bool empty();
	int size();
	void push_back(position);
	void push_front(position);
	position front();
	position back();
	int front_pos();
	int end_pos();
	void clear();
	int left_q, right_q;
	position deque[5000];

};

