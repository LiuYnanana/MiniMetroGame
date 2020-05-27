#include "SubwayHead.h"


SubwayHead::SubwayHead(Route* _route, Station* _station, Track* _track, Map* _map) {
	myLoger = MyLogger::GetInstance();
	ptr_route = _route;
	ptr_station = _station;
	ptr_track = _track;
	ptr_map = _map;
	pos_info.resize(20);
	passager_shape.resize(20);

	owned_sub_head = 3;
	used_sub_head = 0;
	sub_hold_passager = 3;

	for (int i = 0; i < 10; i++) {
		sub_now_pos.push_back(std::make_pair(100, true));
	}
	for (int i = 0; i < 2000; i++) {
		vis[i] = 3;
	}
}

void SubwayHead::GetSubwayHeadNum() {
	head_num_info.clear();
	int x = 40, y = 400;
	LOG4CPLUS_DEBUG(myLoger->rootLog, "supply mouse" << owned_sub_head << " " << used_sub_head);
	for (int i = 0; i < owned_sub_head - used_sub_head; i++) {
		head_num_info.push_back(std::make_pair(x, y));
		x += 15;
	}
}

void SubwayHead::DrawOneSubwayHead(int x, int y) {
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillcircle(x, y, r);

	fillroundrect(x - 18, y - 24, x + 18, y + 19, 10, 10);
	fillcircle(x, y - 20, 2);
	fillrectangle(x - 13, y - 16, x + 13, y + 2);
	fillellipse(x + 2, y - 8, x + 11, y + 2);
	setlinecolor(BLACK);
	line(x - 10, y - 9, x - 7, y - 12);
	line(x - 11, y - 2, x, y - 13);
	fillroundrect(x - 5, y + 9, x + 5, y + 19, 3, 3);
	fillcircle(x - 9, y + 13, 2);
	fillcircle(x - 14, y + 8, 2);
	fillcircle(x + 9, y + 13, 2);
	fillcircle(x + 14, y + 8, 2);

	line(x - 12, y + 19, x - 18, y + 26);
	line(x + 12, y + 19, x + 17, y + 26);
}

void SubwayHead::DrawSubwayHead() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw subwayHead");
	GetSubwayHeadNum();
	for (auto i : head_num_info) {
		int x = i.first, y = i.second;
		DrawOneSubwayHead(x, y);
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "subwayHead is successfully drawn");

}

std::vector<int> SubwayHead::GetShapePoint(int x, int y, int k, int grade) {
	std::vector<int> v;
	if (k == 0) {  //矩形
		v.push_back(x - 2 * grade);
		v.push_back(y - 2 * grade);
		v.push_back(x + 2 * grade);
		v.push_back(y + 2 * grade);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is ractangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(left-top, right-bottom): ("
			<< x - 6 << ", " << y - 6 << "), ("
			<< x + 6 << ", " << y + 6 << ")");
	}
	else if (k == 1) {  //圆
		v.push_back(x);
		v.push_back(y);
		v.push_back(3 * grade);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is circle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(circle-center, radius): ("
			<< x << ", " << y << "), 6");
	}
	else if (k == 2) { //三角形
		v.push_back(x);
		v.push_back(y - 4 * grade);

		v.push_back(x - 3 * grade);
		v.push_back(y + 2 * grade);

		v.push_back(x + 3 * grade);
		v.push_back(y + 2 * grade);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is triangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y + 4 << "), ("
			<< x + 6 << ", " << y + 4 << ")");
	}
	else if (k == 3) { //五角星
		v.push_back(x);
		v.push_back(y - 4 * grade);

		v.push_back(x - 3 * grade);
		v.push_back(y + 2 * grade);

		v.push_back(x + 3 * grade);
		v.push_back(y + 2 * grade);

		v.push_back(x - 3 * grade);
		v.push_back(y - 2 * grade);

		v.push_back(x);
		v.push_back(y + 4 * grade);

		v.push_back(x + 3 * grade);
		v.push_back(y - 2 * grade);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is pentagram");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y + 4 << "), ("
			<< x + 6 << ", " << y + 4 << "), ("
			<< x - 6 << ", " << y - 4 << "), ("
			<< x << ", " << y + 8 << "), ("
			<< x + 6 << ", " << y - 4 << ")");
	}
	else if (k == 4) { //120 53 十字形
		v.push_back(x - 3 * grade);
		v.push_back(y - 1 * grade);
		v.push_back(x + 3 * grade);
		v.push_back(y + 1 * grade);

		v.push_back(x - 1 * grade);
		v.push_back(y - 3 * grade);
		v.push_back(x + 1 * grade);
		v.push_back(y + 3 * grade);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is crisscross");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x + 6 << ", " << y + 2 << "), ("
			<< x - 2 << ", " << y - 6 << "), ("
			<< x + 2 << ", " << y + 6 << ")");
	}
	else if (k == 5) { //五边形
		v.push_back(x);
		v.push_back(y - 4 * grade);

		v.push_back(x - 3 * grade);
		v.push_back(y - 1 * grade);

		v.push_back(x - 2 * grade);
		v.push_back(y + 3 * grade);

		v.push_back(x + 2 * grade);
		v.push_back(y + 3 * grade);

		v.push_back(x + 3 * grade);
		v.push_back(y - 1 * grade);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is fivangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x - 4 << ", " << y + 6 << "), ("
			<< x - 6 << ", " << y - 4 << "), ("
			<< x + 4 << ", " << y + 6 << "), ("
			<< x + 6 << ", " << y - 2 << ")");
	}
	return v;
}


std::pair<int, int> SubwayHead::GetPassagerPos(int k) {
	switch (k)
	{
	case 0:
		return std::make_pair(-5, -7);
	case 1:
		return std::make_pair(5, -7);
	case 2:
		return std::make_pair(-10, 0);
	case 3:
		return std::make_pair(0, 0);
	case 4:
		return std::make_pair(10, 0);
	case 5:
		return std::make_pair(-5, 7);
	case 6:
		return std::make_pair(5, 7);
	default:
		break;
	}
}

std::pair<int, int> SubwayHead::GetNewPos(int sx, int sy, int ex, int ey, int len) {
	double len_se = sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));
	double x = 1.0 * len * (ex - sx) / len_se + sx;
	double y = 1.0 * len * (ey - sy) / len_se + sy;
	return std::make_pair((int)x, (int)y);
}

bool SubwayHead::JudgeRouteChange(int k) {
	return !ptr_route->route_info[k].empty() && !pos_info[k].empty() &&
		ptr_route->route_info[k].front().sx == pos_info[k].front().sx &&
		ptr_route->route_info[k].front().sy == pos_info[k].front().sy &&
		ptr_route->route_info[k].back().ex == pos_info[k].back().ex &&
		ptr_route->route_info[k].back().ey == pos_info[k].back().ey;
}

void SubwayHead::PushStationToBack(int k) {
	int sx = ptr_route->route_info[k].back().sx;
	int sy = ptr_route->route_info[k].back().sy;
	int ex = ptr_route->route_info[k].back().ex;
	int ey = ptr_route->route_info[k].back().ey;

	MyDeque::position t_pos;
	t_pos.sx = sx;
	t_pos.sy = sy;
	t_pos.ex = ex;
	t_pos.ey = ey;
	t_pos.sta_left = false;
	t_pos.sta_right = false;

	LOG4CPLUS_DEBUG(myLoger->rootLog, "sx, sy, ex, ey " << sx << " " << sy << " " << ex << " " << ey);
	int len = sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));

	for (int j = 20; j <= len - 20; j += 10) {
		if (j == 20 || j + 10 >= len - 20) {
			t_pos.wait_pos = true;
			t_pos.sta_left = false;
			t_pos.sta_right = false;
			if (j == 20) {
				t_pos.sta_right = true;
				t_pos.station_id = ptr_route->route_info[k].back().station_sid;
			}
			if (j + 10 > len - 20) {
				t_pos.sta_left = true;
				t_pos.station_id = ptr_route->route_info[k].back().station_eid;
			}

		}
		else t_pos.wait_pos = false;

		LOG4CPLUS_DEBUG(myLoger->rootLog, " back t_pos.station_id " << t_pos.station_id);

		std::pair<int, int> t_pair = GetNewPos(sx, sy, ex, ey, j);
		t_pos.x = t_pair.first;
		t_pos.y = t_pair.second;

		LOG4CPLUS_DEBUG(myLoger->rootLog, "!t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);

		pos_info[k].push_back(t_pos);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);
	}
}

void SubwayHead::PushStationToFront(int k) {
	int sx = ptr_route->route_info[k].front().sx;
	int sy = ptr_route->route_info[k].front().sy;
	int ex = ptr_route->route_info[k].front().ex;
	int ey = ptr_route->route_info[k].front().ey;

	MyDeque::position t_pos;
	t_pos.sx = sx;
	t_pos.sy = sy;
	t_pos.ex = ex;
	t_pos.ey = ey;


	int len = sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));

	for (int j = len - 20; j >= 20; j -= 10) {
		if (j == 20 || j - 10 <= 20) {
			t_pos.wait_pos = true;
			t_pos.sta_left = false;
			t_pos.sta_right = false;
			if (j == 20) {
				t_pos.sta_right = true;
				t_pos.station_id = ptr_route->route_info[k].front().station_sid;
			}
			if (j - 10 < 20) {
				t_pos.sta_left = true;
				t_pos.station_id = ptr_route->route_info[k].front().station_eid;
			}

		}
		else t_pos.wait_pos = false;

		std::pair<int, int> t_pair = GetNewPos(sx, sy, ex, ey, j);
		t_pos.x = t_pair.first;
		t_pos.y = t_pair.second;


		pos_info[k].push_front(t_pos);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);
	}

}

void SubwayHead::GetSubHeadPos(subHead& t_subHead, int i) {
	t_subHead.pos_x = pos_info[i][sub_now_pos[i].first].x;
	t_subHead.pos_y = pos_info[i][sub_now_pos[i].first].y;
	t_subHead.wait_pos = pos_info[i][sub_now_pos[i].first].wait_pos;
	t_subHead.sta_left = pos_info[i][sub_now_pos[i].first].sta_left;
	t_subHead.sta_right = pos_info[i][sub_now_pos[i].first].sta_right;
	t_subHead.station_id = pos_info[i][sub_now_pos[i].first].station_id;

	LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead sta_left" << t_subHead.sta_left << " " << t_subHead.sta_right);

	t_subHead.route_id = i;
	t_subHead.subHead_size = sub_hold_passager;
	t_subHead.subHead_num = 0;
	t_subHead.director = sub_now_pos[i].second;

	if (sub_now_pos[i].second == true) {
		if (sub_now_pos[i].first == pos_info[i].end_pos() - 1) {
			sub_now_pos[i].second = false;
		}
		else {
			if (t_subHead.wait_pos == true && vis[sub_now_pos[i].first]) {
				vis[sub_now_pos[i].first]--;
				sub_now_pos[i].first--;
			}
			else {
				vis[sub_now_pos[i].first] = 3;
			}
			sub_now_pos[i].first++;
		}

	}
	else {
		if (sub_now_pos[i].first == pos_info[i].front_pos()) {
			sub_now_pos[i].second = true;
		}
		else {

			if (t_subHead.wait_pos == true && vis[sub_now_pos[i].first]) {
				vis[sub_now_pos[i].first]--;
				sub_now_pos[i].first++;
			}
			else {
				vis[sub_now_pos[i].first] = 3;
			}
			sub_now_pos[i].first--;
		}
	}

	LOG4CPLUS_DEBUG(myLoger->rootLog, "sub_now_pos[i].first " << sub_now_pos[i].first << " " << sub_now_pos[i].second <<
		" " << "deque left right " << pos_info[i].front_pos() << " " << pos_info[i].end_pos());
	LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead info: (pos.x, pos.y) " << t_subHead.pos_x << " " << t_subHead.pos_y
		<< "; t_subHead.wait_pos " << t_subHead.wait_pos << "t_subHead.director " << t_subHead.director
		<< " t_subHead.sta_right" << t_subHead.sta_right << "t_subHead.sta_left " << t_subHead.sta_left);
}

void SubwayHead::DealPassagers(subHead& t_subHead, int i) {
	//-----------------乘客上下车----------
	if (t_subHead.wait_pos) {       //载客
		if (t_subHead.director) {    // 从前往后行驶
			if (t_subHead.sta_right) { //上车
				if (passager_shape[i].size() < sub_hold_passager) {
					LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead.station_id " << t_subHead.station_id);
					for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "!possager info " << i.shape);
					}

					std::vector<Station::passager_shape>::iterator it;
					for (it = ptr_station->sta_passager_pos[t_subHead.station_id].begin();
						it != ptr_station->sta_passager_pos[t_subHead.station_id].end(); ) {

						if (ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][1][it->shape]) {
							passager_shape[i].push_back(it->shape);
							it = ptr_station->sta_passager_pos[t_subHead.station_id].erase(it);
						}
						else it++;

						if (passager_shape[i].size() >= sub_hold_passager) break;
					}

					for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "!possager info " << i.shape);
					}
				}

				ptr_station->mu_station.lock();
				int cnt = 0;
				for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
					std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, cnt++);
					std::vector<int> v = ptr_station->GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
						ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
						i.shape, 1);
				}
				ptr_station->mu_station.unlock();
			}

			if (t_subHead.sta_left) { //下车
				for (std::vector<int>::iterator it = passager_shape[i].begin();
					it != passager_shape[i].end(); ) {
					LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead.station_id]" << t_subHead.station_id);

					int next_sta = ptr_route->Next_station[t_subHead.route_id][t_subHead.station_id][1];
					if (ptr_map->v_station_shape[t_subHead.station_id] == *it) {
						it = passager_shape[i].erase(it);
					}
					else if (!ptr_route->station_arrive[next_sta][t_subHead.route_id][1][*it]
						&& ptr_station->sta_passager_pos[t_subHead.station_id].size() < 8) {
						std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, -1);
						std::vector<int> v = GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
							ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
							*it, 1);
						
						Station::passager_shape t_struct;
						t_struct.shape = *it;
						t_struct.v_point = v;
						ptr_station->sta_passager_pos[t_subHead.station_id].push_back(t_struct);

						it = passager_shape[i].erase(it);
					}
					else {
						it++;
					}
				}
			}

		}
		else {
			if (t_subHead.sta_left) { //上车
				LOG4CPLUS_DEBUG(myLoger->rootLog, "back upupup" );
				if (passager_shape[i].size() < sub_hold_passager) {

					for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "!possager info " << i.shape);
					}

					std::vector<Station::passager_shape>::iterator it;
					for (it = ptr_station->sta_passager_pos[t_subHead.station_id].begin();
						it != ptr_station->sta_passager_pos[t_subHead.station_id].end(); ) {

						LOG4CPLUS_DEBUG(myLoger->rootLog, "station shape" << it->shape);
						LOG4CPLUS_DEBUG(myLoger->rootLog, "station shape" << 
							ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][0][it->shape]);
						if (ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][0][it->shape]) {
							passager_shape[i].push_back(it->shape);
							it = ptr_station->sta_passager_pos[t_subHead.station_id].erase(it);
						}
						else it++;

						if (passager_shape[i].size() >= sub_hold_passager) break;
					}

					for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "!possager info " << i.shape);
					}
				}

				ptr_station->mu_station.lock();
				int cnt = 0;
				for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
					std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, cnt++);
					std::vector<int> v = ptr_station->GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
						ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
						i.shape, 1);
				}
				ptr_station->mu_station.unlock();
			}
			 
			if (t_subHead.sta_right) { //下车
				LOG4CPLUS_DEBUG(myLoger->rootLog, "back downdown");
				for (std::vector<int>::iterator it = passager_shape[i].begin();
					it != passager_shape[i].end(); ) {
					LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead.station_id]" << t_subHead.station_id);

					int next_sta = ptr_route->Next_station[t_subHead.route_id][t_subHead.station_id][0];

					if (ptr_map->v_station_shape[t_subHead.station_id] == *it) {
						it = passager_shape[i].erase(it);
					}
					else if (!ptr_route->station_arrive[next_sta][t_subHead.route_id][0][*it]
						&& ptr_station->sta_passager_pos[t_subHead.station_id].size() < 8) {
						std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, -1);
						std::vector<int> v = GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
							ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
							*it, 1);

						Station::passager_shape t_struct;
						t_struct.shape = *it;
						t_struct.v_point = v;
						ptr_station->sta_passager_pos[t_subHead.station_id].push_back(t_struct);

						it = passager_shape[i].erase(it);
					}
					else {
						it++;
					}
				}
			}
		}
	}
}

void SubwayHead::GetSubwayHeadInfo() {
	while (true) {
		mu_sub_head.lock();
		for(int k = 0; k < ptr_route->route_info.size(); k++) {
			
			LOG4CPLUS_DEBUG(myLoger->rootLog, "!!subwayHead");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "!!subwayHead" << ptr_route->route_info[k].front().sx << " " << ptr_route->route_info[k].front().sy <<
			" " << ptr_route->route_info[k].back().ex << " " << ptr_route->route_info[k].back().ey);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "!!subwayHead" << pos_info[k].front().sx << " " << ptr_route->route_info[k].front().sy <<
			" " << pos_info[k].back().ex << " " << pos_info[k].back().ey);

			if (JudgeRouteChange(k)) continue;   //线路没有改变
			if (ptr_route->route_info[k].empty()) continue;
			
			if (ptr_route->route_info[k].back().ex != pos_info[k].back().ex ||
				ptr_route->route_info[k].back().ey != pos_info[k].back().ey) {  // 向后push站点
				PushStationToBack(k);
			}

			if (ptr_route->route_info[k].front().sx != pos_info[k].front().sx ||
				ptr_route->route_info[k].front().sy != pos_info[k].front().sy) { //front 增加路线
				PushStationToFront(k);
			}

		}
		subHead_info.clear();
	
		for (int i = 0; i < ptr_route->route_info.size(); i++) {   // 跑n条线路
			if (pos_info[i].empty()) continue;

			subHead t_subHead;
			GetSubHeadPos(t_subHead, i);
			DealPassagers(t_subHead, i);
			subHead_info.push_back(t_subHead);

		}

		for (int i = 0; i < subHead_info.size(); i++) {
			LOG4CPLUS_DEBUG(myLoger->rootLog, "!subHead info" << subHead_info[i].pos_x << " " << 
			subHead_info[i].pos_y << " " << subHead_info[i].wait_pos);
		}
		mu_sub_head.unlock();
		Sleep(100);

	}

}

void SubwayHead::DrawSubwayHeadMove() {
	//for (auto t_dq : pos_info) {
	//	LOG4CPLUS_DEBUG(myLoger->rootLog, "pos_info: ");
	//	for (int i = t_dq.front_pos(); i < t_dq.end_pos(); i++) {
	//		LOG4CPLUS_DEBUG(myLoger->rootLog, "t_dp info" << t_dq[i].sx << " " << t_dq[i].sy <<
	//			" " << t_dq[i].ex << " " << t_dq[i].ey << "; " << t_dq[i].x << " " << t_dq[i].y);

	//		setfillcolor(RED);
	//		solidcircle(t_dq[i].x, t_dq[i].y, 2);
	//	}
	//}
	mu_sub_head.lock();
	for (int i = 0; i < subHead_info.size(); i++) {
		setlinecolor(Color::get_color(ptr_track->track_color[subHead_info[i].route_id]));
		circle(subHead_info[i].pos_x, subHead_info[i].pos_y, 15);
		for (int j = 0; j < passager_shape[i].size(); j++) {
			LOG4CPLUS_DEBUG(myLoger->rootLog, "passaget_shape" << passager_shape[i].size());
			std::pair<int, int> t_p = GetPassagerPos(j);
			LOG4CPLUS_DEBUG(myLoger->rootLog, "passaget_shape distance" << i << " " << j << " "
				<< passager_shape[i][j]);
			LOG4CPLUS_DEBUG(myLoger->rootLog, "passaget_shape" << subHead_info.size());
			LOG4CPLUS_DEBUG(myLoger->rootLog, "passaget_shape distance" << subHead_info[i].pos_x << " " 
				<< subHead_info[i].pos_y);
			LOG4CPLUS_DEBUG(myLoger->rootLog, "passaget_shape distance" << t_p.first << " " << t_p.second);
			std::vector<int> v = GetShapePoint(subHead_info[i].pos_x + t_p.first, 
				subHead_info[i].pos_y + t_p.second, passager_shape[i][j], 1);

			if (passager_shape[i][j] == 3 || passager_shape[i][j] == 4) {
				setfillcolor(Color::get_color(ptr_track->track_color[subHead_info[i].route_id]));
				Graphics::DrawGraphics(passager_shape[i][j] * 2, v);
			}
			else {
				LOG4CPLUS_DEBUG(myLoger->rootLog, "i " << i);
				LOG4CPLUS_DEBUG(myLoger->rootLog, subHead_info.size());

				LOG4CPLUS_DEBUG(myLoger->rootLog, "!subHead_info[i].route_id" << subHead_info[i].route_id);
				setlinecolor(Color::get_color(ptr_track->track_color[subHead_info[i].route_id]));
				setfillcolor(Color::get_color(ptr_track->track_color[subHead_info[i].route_id]));
				Graphics::DrawGraphics(passager_shape[i][j] * 2 + 1, v);
			}
			//Graphics::DrawGraphics(subHead_info[i].passager_shape[j] * 2 + 1, v);

		}
	}
	mu_sub_head.unlock();

}

SubwayHead::~SubwayHead() {}