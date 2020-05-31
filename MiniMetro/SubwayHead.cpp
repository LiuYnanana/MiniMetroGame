#include "SubwayHead.h"


SubwayHead::SubwayHead(Route* _route, Station* _station, Track* _track, Map* _map) {
	myLoger = MyLogger::GetInstance();
	ptr_route = _route;
	ptr_station = _station;
	ptr_track = _track;
	ptr_map = _map;
	
	for (int i = 0; i < 10; i++) {
		MyDeque _mydq;
		LOG4CPLUS_ERROR(myLoger->rootLog, "构造 " << _mydq.left_q << " " << _mydq.right_q);
		pos_info.push_back(_mydq);

	}
	for(int i = 0; i < 10; i++)
	passager_shape[i].resize(20);
	
	have_sub_head = true;
	select_sub = false;
	owned_sub_head = 3;
	used_sub_head = 0;
	sub_hold_passager = 3;

	for (int i = 0; i < 10; i++) {
		subHead_num[i] = 1;
		for (int j = 0; j < 10; j++) {
			sub_now_pos[i].push_back(std::make_pair(2501 , true));
		}
	}
	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 5000; i++) {
			vis[k][i] = 3;
		}
	}
	
}

void SubwayHead::GetSubwayHeadNum() {
	head_num_info.clear();
	int x = 40, y = 400;
	LOG4CPLUS_DEBUG(myLoger->rootLog, "supply mouse" << owned_sub_head << " " << used_sub_head);
	if (owned_sub_head - used_sub_head == 0) have_sub_head = false;
	else have_sub_head = true;
	for (int i = 0; i < owned_sub_head - used_sub_head; i++) {
		head_num_info.push_back(std::make_pair(x, y));
		x += 15;
	}
}

void SubwayHead::GetSubwaySelect()
{
	int x = 20, y = 345;
	for (int i = 0; i < ptr_track->used_track; i++) {
		select_subway.push_back(std::make_pair(x, y));
		x += 25;
	}
	x = 30;
	y = 325;
	for (int i = 4; i < ptr_track->used_track; i++) {
		select_subway.push_back(std::make_pair(x, y));
		x += 25;
	}
}

void SubwayHead::DrawNoSubwayHead()
{
	if (!have_sub_head) {
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("黑体"));

		TCHAR s[] = _T("无可用地铁");
		outtextxy(10, 400, s);
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

void SubwayHead::DrawSubwaySelect()
{
	if (select_sub) {
		setcolor(BLACK);
		setfillcolor(WHITE);
		fillrectangle(5, 310, 110, 360);
		for (int i = 0; i < select_subway.size(); i++) {
			int x = select_subway[i].first, y = select_subway[i].second;
			fillcircle(x, y, 10);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(18, 0, _T("黑体"));
			TCHAR s[5];
			_stprintf(s, _T("%d"), i + 1);
			outtextxy(x - 4, y - 8, s);
		}
		//fillrectangle(100, 310, 110, 320);
		fillcircle(102, 318, 6);
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("黑体"));
		TCHAR s[] = _T("x");
		outtextxy(99, 308, s);
	}
}

void SubwayHead::DrawSubwayHead() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw subwayHead");
	GetSubwayHeadNum();
	for (auto i : head_num_info) {
		int x = i.first, y = i.second;
		DrawOneSubwayHead(x, y);
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "subwayHead is successfully drawn");
	if (!have_sub_head) {
		DrawNoSubwayHead();
		select_sub = false;
	}

	if (select_sub) {
		select_subway.clear();
		GetSubwaySelect();
		DrawSubwaySelect();
	}
	
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


void SubwayHead::GetSelectInfo()
{
	bool flag = false;
	while (true) {
		//ptr_map->mu_mouse.lock();
		flag = false;
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			LOG4CPLUS_DEBUG(myLoger->rootLog, "mouse subway " << m.x << " " << m.y);
			if (m.mkLButton == true && JudgeOnSubPic(m.x, m.y)) {
				select_sub = true;
			}
			else if (m.mkLButton == true && JudgeCloseSubPic(m.x, m.y)) {
				select_sub = false;
			}
			else if (m.mkLButton == true && select_sub) {
				if (!have_sub_head) continue;
				for (int i = 0; i < select_subway.size(); i++) {
					int x = select_subway[i].first, y = select_subway[i].second;
					if ((m.x - x) * (m.x - x) + (m.y - y) * (m.y - y) <= 10 * 10) {
						subHead_num[i]++;
						used_sub_head++;
						LOG4CPLUS_ERROR(myLoger->rootLog, "点击增加地铁 " << subHead_num[i] << " " << used_sub_head);
						select_sub = false;
						Sleep(3000);
						break;
					}
				}
			}
		}	
		//ptr_map->mu_mouse.unlock();
	}
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

bool SubwayHead::JudgeOnSubPic(int mx, int my)
{
	for (int i = 0; i < head_num_info.size(); i++) {
		int x = head_num_info[i].first, y = head_num_info[i].second;
		LOG4CPLUS_DEBUG(myLoger->rootLog, x << " " << y);
		if ((x - mx) * (x - mx) + (y - my) * (y - my) <= 34 * 34)
			return true;
	}
	return false;
}

bool SubwayHead::JudgeCloseSubPic(int mx, int my)
{
	if ((mx - 102) * (mx - 102) + (my - 318) * (my - 318) <= 36)
		return true;
	return false;
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
	
	LOG4CPLUS_DEBUG(myLoger->rootLog, "sx, sy, ex, ey " << sx << " " << sy << " " << ex << " " << ey);
	int len = sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));

	for (int j = 10; j <= len - 10; j += 2) {
		t_pos.sta_left = false;
		t_pos.sta_right = false;
		t_pos.sx = sx;
		t_pos.sy = sy;
		t_pos.ex = ex;
		t_pos.ey = ey;
		t_pos.station_id = -1;
		t_pos.wait_pos = false;

		if (j == 10 || j + 2 > len - 10) {
			t_pos.wait_pos = true;
			if (j == 10) {
				t_pos.sta_right = true;
				t_pos.station_id = ptr_route->route_info[k].back().station_sid;
			}
			if (j + 2 > len - 10) {
				t_pos.sta_left = true;
				t_pos.station_id = ptr_route->route_info[k].back().station_eid;
			}
		}

		LOG4CPLUS_DEBUG(myLoger->rootLog, " back t_pos.station_id " << t_pos.station_id);

		std::pair<int, int> t_pair = GetNewPos(sx, sy, ex, ey, j);
		t_pos.x = t_pair.first;
		t_pos.y = t_pair.second;

		LOG4CPLUS_DEBUG(myLoger->rootLog, "!t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);

		LOG4CPLUS_ERROR(myLoger->rootLog, k << " 双向对列 前后端 " << pos_info[k].front_pos() <<
			" " << pos_info[k].end_pos());

		pos_info[k].push_back(t_pos);
		LOG4CPLUS_ERROR(myLoger->rootLog, "t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);
		LOG4CPLUS_ERROR(myLoger->rootLog, "station_id" << t_pos.station_id << " " << t_pos.sta_left <<
			" " << t_pos.sta_right);
	}
}

void SubwayHead::PushStationToFront(int k) {
	int sx = ptr_route->route_info[k].front().sx;
	int sy = ptr_route->route_info[k].front().sy;
	int ex = ptr_route->route_info[k].front().ex;
	int ey = ptr_route->route_info[k].front().ey;

	MyDeque::position t_pos;
	int len = sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));

	for (int j = len - 10; j >= 10; j -= 2) {
		t_pos.sx = sx;
		t_pos.sy = sy;
		t_pos.ex = ex;
		t_pos.ey = ey;
		t_pos.station_id = -1;
		t_pos.wait_pos = false;
		if (j == len - 10 || j - 2 < 10) {
			t_pos.wait_pos = true;
			t_pos.sta_left = false;
			t_pos.sta_right = false;
			if (j == len - 10) {
				t_pos.sta_left = true;
				t_pos.station_id = ptr_route->route_info[k].front().station_eid;
			}
			if (j - 2 < 10) {
				t_pos.sta_right = true;
				t_pos.station_id = ptr_route->route_info[k].front().station_sid;
			}

		}
	

		std::pair<int, int> t_pair = GetNewPos(sx, sy, ex, ey, j);
		t_pos.x = t_pair.first;
		t_pos.y = t_pair.second;

		LOG4CPLUS_ERROR(myLoger->rootLog, k << "2号的变化 " << pos_info[2].front_pos() <<
			" " << pos_info[2].end_pos());
		LOG4CPLUS_ERROR(myLoger->rootLog, k << " 双向对列 前后端 " << pos_info[k].front_pos() <<
			" " << pos_info[k].end_pos());
		pos_info[k].push_front(t_pos);
		LOG4CPLUS_ERROR(myLoger->rootLog, "t_pos info" << t_pos.sx << " " << t_pos.sy <<
			" " << t_pos.ex << " " << t_pos.ey << "; " << t_pos.x << " " << t_pos.y);
		LOG4CPLUS_ERROR(myLoger->rootLog, "station_id" << t_pos.station_id << " " << t_pos.sta_left <<
			" " << t_pos.sta_right);
	}

}

void SubwayHead::GetSubHeadPos(subHead& t_subHead, int i, int j) {
	LOG4CPLUS_ERROR(myLoger->rootLog,  "2号的变化 " << pos_info[2].front_pos() <<
		" " << pos_info[2].end_pos());
	LOG4CPLUS_ERROR(myLoger->rootLog, "GetSubHeadPos" << i << " " << sub_now_pos[i][j].first);
	t_subHead.pos_x = pos_info[i][sub_now_pos[i][j].first].x;
	t_subHead.pos_y = pos_info[i][sub_now_pos[i][j].first].y;
	t_subHead.wait_pos = pos_info[i][sub_now_pos[i][j].first].wait_pos;
	t_subHead.sta_left = pos_info[i][sub_now_pos[i][j].first].sta_left;
	t_subHead.sta_right = pos_info[i][sub_now_pos[i][j].first].sta_right;
	t_subHead.station_id = pos_info[i][sub_now_pos[i][j].first].station_id;

	
	 
	t_subHead.route_id = i;
	t_subHead.subHead_size = sub_hold_passager;
	t_subHead.subHead_num = 0;
	t_subHead.director = sub_now_pos[i][j].second;

	if (sub_now_pos[i][j].second == true) {
		if (sub_now_pos[i][j].first == pos_info[i].end_pos() - 1) {
			sub_now_pos[i][j].second = false;
		}
		else {
			if (t_subHead.wait_pos == true && vis[i][sub_now_pos[i][j].first]) {
				vis[i][sub_now_pos[i][j].first]--;
				sub_now_pos[i][j].first--;
			}
			else {
				vis[i][sub_now_pos[i][j].first] = 3;
			}
			sub_now_pos[i][j].first++;
		}

	}
	else {
		if (sub_now_pos[i][j].first == pos_info[i].front_pos()) {
			sub_now_pos[i][j].second = true;
		}
		else {

			if (t_subHead.wait_pos == true && vis[i][sub_now_pos[i][j].first]) {
				vis[i][sub_now_pos[i][j].first]--;
				sub_now_pos[i][j].first++;
			}
			else {
				vis[i][sub_now_pos[i][j].first] = 3;
			}
			sub_now_pos[i][j].first--;
		}
	}

	LOG4CPLUS_DEBUG(myLoger->rootLog, "sub_now_pos[i].first " << sub_now_pos[i][j].first << " " << sub_now_pos[i][j].second <<
		" " << "deque left right " << pos_info[i].front_pos() << " " << pos_info[i].end_pos());
	LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead info: (pos.x, pos.y) " << t_subHead.pos_x << " " << t_subHead.pos_y
		<< "; t_subHead.wait_pos " << t_subHead.wait_pos << "t_subHead.director " << t_subHead.director
		<< " t_subHead.sta_right" << t_subHead.sta_right << "t_subHead.sta_left " << t_subHead.sta_left);
}

void SubwayHead::DealPassagers(subHead& t_subHead, int i, int j) {
	LOG4CPLUS_ERROR(myLoger->rootLog,  "2号的变化 " << pos_info[2].front_pos() <<
		" " << pos_info[2].end_pos());
	//-----------------乘客上下车----------
	LOG4CPLUS_ERROR(myLoger->rootLog, "这里车站号 " << t_subHead.station_id);
	if (t_subHead.wait_pos) {       //载客
		if (t_subHead.director) {    // 从前往后行驶
			LOG4CPLUS_ERROR(myLoger->rootLog, "车从先向后行驶");
			if (t_subHead.sta_right) { //上车
				LOG4CPLUS_ERROR(myLoger->rootLog, "上车");
				if (passager_shape[i][j].size() < sub_hold_passager) {
					LOG4CPLUS_ERROR(myLoger->rootLog, "车站号 " << t_subHead.station_id);
			/*		for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_ERROR(myLoger->rootLog, "该站乘客形状" << i.shape);
					}*/

					std::vector<Station::passager_shape>::iterator it;
					for (it = ptr_station->sta_passager_pos[t_subHead.station_id].begin();
						it != ptr_station->sta_passager_pos[t_subHead.station_id].end(); ) {

						LOG4CPLUS_ERROR(myLoger->rootLog, " 正向 map 车站 路线 形状 这条路能否到达" << t_subHead.station_id << " " << t_subHead.route_id
						<< " " << it->shape << " " <<ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][1][it->shape]);

						if (ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][1][it->shape]) {
							passager_shape[i][j].push_back(it->shape);
							LOG4CPLUS_ERROR(myLoger->rootLog,  it->shape << "形状上车了");
							it = ptr_station->sta_passager_pos[t_subHead.station_id].erase(it);
						}
						else it++;

						if (passager_shape[i][j].size() >= sub_hold_passager) break;
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
				for (std::vector<int>::iterator it = passager_shape[i][j].begin();
					it != passager_shape[i][j].end(); ) {
					LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead.station_id]" << t_subHead.station_id);

					
					int next_sta = ptr_route->Next_station[t_subHead.route_id][t_subHead.station_id][1];
					LOG4CPLUS_DEBUG(myLoger->rootLog, "next_sta" << next_sta);
					if (ptr_map->v_station_shape[t_subHead.station_id] == *it) {
						it = passager_shape[i][j].erase(it);
					}
					else if (next_sta == -1 || (next_sta != -1 && !ptr_route->station_arrive[next_sta][t_subHead.route_id][1][*it]
						&& ptr_station->sta_passager_pos[t_subHead.station_id].size() < 8)) {
						std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, -1);
						std::vector<int> v = GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
							ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
							*it, 1);
						
						Station::passager_shape t_struct;
						t_struct.shape = *it;
						t_struct.v_point = v;
						ptr_station->sta_passager_pos[t_subHead.station_id].push_back(t_struct);

						it = passager_shape[i][j].erase(it);
					}
					else {
						it++;
					}
				}
			}

		}
		else {
			LOG4CPLUS_ERROR(myLoger->rootLog, "车从后往前行驶");
			if (t_subHead.sta_left) { //上车
				LOG4CPLUS_ERROR(myLoger->rootLog, "上车");
				if (passager_shape[i][j].size() < sub_hold_passager) {

					for (auto i : ptr_station->sta_passager_pos[t_subHead.station_id]) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "!possager info " << i.shape);
					}
					LOG4CPLUS_ERROR(myLoger->rootLog, "车站号 " << t_subHead.station_id);
					std::vector<Station::passager_shape>::iterator it;
					for (it = ptr_station->sta_passager_pos[t_subHead.station_id].begin();
						it != ptr_station->sta_passager_pos[t_subHead.station_id].end(); ) {

						LOG4CPLUS_ERROR(myLoger->rootLog, " 反向 map 车站 路线 形状 这条路能否到达" << t_subHead.station_id << " " << t_subHead.route_id
							<< " " << it->shape << " " << ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][1][it->shape]);

						if (ptr_route->station_arrive[t_subHead.station_id][t_subHead.route_id][0][it->shape]) {
							passager_shape[i][j].push_back(it->shape);
							LOG4CPLUS_ERROR(myLoger->rootLog, it->shape << "形状上车了");
							it = ptr_station->sta_passager_pos[t_subHead.station_id].erase(it);
						}
						else it++;

						if (passager_shape[i][j].size() >= sub_hold_passager) break;
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
				for (std::vector<int>::iterator it = passager_shape[i][j].begin();
					it != passager_shape[i][j].end(); ) {
					LOG4CPLUS_DEBUG(myLoger->rootLog, "t_subHead.station_id]" << t_subHead.station_id);

					int next_sta = ptr_route->Next_station[t_subHead.route_id][t_subHead.station_id][0];
					LOG4CPLUS_DEBUG(myLoger->rootLog, "next_sta" << next_sta);
					if (ptr_map->v_station_shape[t_subHead.station_id] == *it) {
						it = passager_shape[i][j].erase(it);
					}
					else if (next_sta == -1 || (next_sta != -1 && !ptr_route->station_arrive[next_sta][t_subHead.route_id][0][*it]
						&& ptr_station->sta_passager_pos[t_subHead.station_id].size() < 8)) {
						std::pair<int, int> offset = ptr_station->GetPassagerOffset(t_subHead.station_id, -1);
						std::vector<int> v = GetShapePoint(ptr_map->sta_appear[t_subHead.station_id].first + offset.first,
							ptr_map->sta_appear[t_subHead.station_id].second + offset.second,
							*it, 1);

						Station::passager_shape t_struct;
						t_struct.shape = *it;
						t_struct.v_point = v;
						ptr_station->sta_passager_pos[t_subHead.station_id].push_back(t_struct);

						it = passager_shape[i][j].erase(it);
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
			if (JudgeRouteChange(k)) continue;   //线路没有改变
			if (ptr_route->route_info[k].empty()) continue;
			
			if (ptr_route->route_info[k].back().ex != pos_info[k].back().ex ||
				ptr_route->route_info[k].back().ey != pos_info[k].back().ey) {  // 向后push站点
				LOG4CPLUS_ERROR(myLoger->rootLog, "向后添加站点");
				LOG4CPLUS_ERROR(myLoger->rootLog,  "2号的变化 " << pos_info[2].front_pos() <<
					" " << pos_info[2].end_pos());
				PushStationToBack(k);
				LOG4CPLUS_ERROR(myLoger->rootLog, "2号的变化 " << pos_info[2].front_pos() <<
					" " << pos_info[2].end_pos());
			}
			LOG4CPLUS_ERROR(myLoger->rootLog, "2号的变化 " << pos_info[2].front_pos() <<
				" " << pos_info[2].end_pos());
			if (ptr_route->route_info[k].front().sx != pos_info[k].front().sx ||
				ptr_route->route_info[k].front().sy != pos_info[k].front().sy) { //front 增加路线
				LOG4CPLUS_ERROR(myLoger->rootLog, "向前添加站点");
				LOG4CPLUS_ERROR(myLoger->rootLog,  "2号的变化 " << pos_info[2].front_pos() <<
					" " << pos_info[2].end_pos());
				PushStationToFront(k);
			}

		}
		for(int i = 0; i < 10; i++) 
		subHead_info[i].clear();
	
		for (int i = 0; i < ptr_route->route_info.size(); i++) { // 跑n条线路
			if (pos_info[i].empty()) continue;
			LOG4CPLUS_ERROR(myLoger->rootLog, "第" << i << "条线路的地铁数量 " << subHead_num[i]);
			for (int j = 0; j < subHead_num[i]; j++) {
				LOG4CPLUS_ERROR(myLoger->rootLog, "跑第" << i << "条线路 " << j);
				subHead t_subHead;
				GetSubHeadPos(t_subHead, i, j);
				DealPassagers(t_subHead, i, j);
				subHead_info[i].push_back(t_subHead);
			}
		}
		mu_sub_head.unlock();
		Sleep(100);
	}
}

void SubwayHead::DrawSubwayHeadMove() {
	mu_sub_head.lock();
	for (int i = 0; i < ptr_track->used_track; i++) {
		for (int j = 0; j < subHead_info[i].size(); j++) {
			setlinecolor(Color::get_color(ptr_track->track_color[subHead_info[i][j].route_id]));
			circle(subHead_info[i][j].pos_x, subHead_info[i][j].pos_y, 15);
			for (int k = 0; k < passager_shape[i][j].size(); k++) {
				std::pair<int, int> t_p = GetPassagerPos(k);
				std::vector<int> v = GetShapePoint(subHead_info[i][j].pos_x + t_p.first,
					subHead_info[i][j].pos_y + t_p.second, passager_shape[i][j][k], 1);

				if (passager_shape[i][j][k] == 3 || passager_shape[i][j][k] == 4) {
					setfillcolor(Color::get_color(ptr_track->track_color[subHead_info[i][j].route_id]));
					Graphics::DrawGraphics(passager_shape[i][j][k] * 2, v);
				}
				else {
					setlinecolor(Color::get_color(ptr_track->track_color[subHead_info[i][j].route_id]));
					setfillcolor(Color::get_color(ptr_track->track_color[subHead_info[i][j].route_id]));
					Graphics::DrawGraphics(passager_shape[i][j][k] * 2 + 1, v);
				}
			}
		}
	}
	mu_sub_head.unlock();

}

SubwayHead::~SubwayHead() {}