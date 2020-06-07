#include "Station.h"

Station::Station(Map *mp){
	ptr_map = mp;
	sta_passager_pos.resize(100);
	gameover = false;
}

Station::~Station(){}

int Station::RandPassagerTime() { 
	srand(time(NULL));
	int k = sqrt(rand() % 30);
	return k;
}

std::vector<int> Station::GetShapePoint(int x, int y, int k, int grade) {
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

std::pair<int, int> Station::GetPassagerOffset(int k, int cnt) {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "get passager offset start... " << k);
	int num;
	if (cnt == -1)
		num = sta_passager_pos[k].size();
	else num = cnt;
	//if (num > 7) return std::make_pair(-1, -1);
	LOG4CPLUS_DEBUG(myLoger->rootLog, "sta_passager_pos[" << k << "].size is" << num);
	switch (num)
	{
	case 0:
		return std::make_pair(12, -5);
	case 1:
		return std::make_pair(20, -5);
	case 2:
		return std::make_pair(28, -5);
	case 3:
		return std::make_pair(36, -5);
	case 4:
		return std::make_pair(12, 4);
	case 5:
		return std::make_pair(20, 4);
	case 6:
		return std::make_pair(28, 4);
	case 7:
		return std::make_pair(36, 4);
	default:
		break;
	}
}

void Station::GetWarningInfo(int k, int t) {
	int x = ptr_map->sta_appear[k].first;
	int y = ptr_map->sta_appear[k].second;

	double PI = acos(-1);
	//mu_warning.lock();
	LOG4CPLUS_ERROR(myLoger->rootLog, "push line " << t);
	warnning[k].clear();
	for (int i = 1; i <= t; i++) {

		//mu_draw.lock();
		int x2 = static_cast<int>(x + (sin(i * (PI / 30))) * 4);
		int y2 = static_cast<int>(y - (cos(i * (PI / 30))) * 4);

		warn_line t_line;
		t_line.sx = x;
		t_line.sy = y;
		t_line.ex = x2;
		t_line.ey = y2;
		warnning[k].push_back(t_line);
	}
	//mu_warning.unlock();

}

void Station::DrawPassagerWarning()
{
//	mu_warning.lock();
	for (int i = 0; i < ptr_map->sta_appear.size(); i++) {
		if (warnning[i].empty()) continue;
		LOG4CPLUS_ERROR(myLoger->rootLog, "warnning[i].size " << warnning[i].size());
		for (auto l : warnning[i]) {
			setlinecolor(RED);
			line(l.sx, l.sy, l.ex, l.ey);
		}
	}
	//LOG4CPLUS_ERROR(myLoger->rootLog, "gameover " << gameover);
	if (gameover) DrawEndPicture();
	//mu_warning.unlock();
}

void Station::CanclePassagerWarning(int k) {
	warnning[k].clear();
	LOG4CPLUS_ERROR(myLoger->rootLog, "warnning " << warnning[k].size());

}

void Station::GetStationPassagerInfo() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "Draw Station Passager start...");
	srand(time(NULL));
	while (true) {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "sta_appear num is " << ptr_map->sta_appear.size());
		if (ptr_map->sta_appear.size() == 0) {
			Sleep(1000);
			continue;
		}

		int sta_num;
		
		mu_warning.lock();
		do {
			sta_num = rand() % ptr_map->sta_appear.size(); //确定给哪个站点增加新乘客
			LOG4CPLUS_DEBUG(myLoger->rootLog, "the passager at " << sta_num << "station");
		} while (find_if(sta_overtime.begin(), sta_overtime.end(), [
			sta_num](const std::pair<int, int> a) {return a.first == sta_num; }) != sta_overtime.end());
		mu_warning.unlock();

		LOG4CPLUS_ERROR(myLoger->rootLog, "finally the passager at " << sta_num << "station");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_shape have:");

		LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_num start rand...");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "v_station_shape[sta_num] is " << ptr_map->v_station_shape[sta_num]);
		
		int shape_num;
		do{                               
			shape_num = rand() % ptr_map->v_station_shape.size(); //确定增加什么类型的乘客
			LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_num is " << shape_num);
		} while (ptr_map->v_station_shape[shape_num] == ptr_map->v_station_shape[sta_num]);
		
		mu_station.lock();
	

	    //passager_shape t_struct;
		//t_struct.shape = ptr_map->v_station_shape[shape_num];
		//t_struct.v_point = v;
		sta_passager_pos[sta_num].push_back(ptr_map->v_station_shape[shape_num]);

		LOG4CPLUS_ERROR(myLoger->rootLog, "the station id is " << sta_num);
		for (auto i : sta_passager_pos[sta_num]) {
			LOG4CPLUS_ERROR(myLoger->rootLog, "the shape_num is " << i);
		}
		mu_station.unlock();
		LOG4CPLUS_ERROR(myLoger->rootLog, "sta_passager " << sta_passager_pos[sta_num].size());
		if (sta_passager_pos[sta_num].size() == 8) { //車站到達最大承載量
			LOG4CPLUS_ERROR(myLoger->rootLog, "第 " << sta_num << "个车站，人数超量");
			sta_overtime.push_back(std::make_pair(sta_num, time(NULL)));
		
		}
		int t = RandPassagerTime();
		LOG4CPLUS_DEBUG(myLoger->rootLog, "passager appear time " << t);
		if (end) return;
		Sleep(t * 1000);
	}

}

void Station::DrawStationPassager() {
	for (int i = 0; i < sta_passager_pos.size(); i++) {
		for(int j = 0; j < sta_passager_pos[i].size(); j++) {
			int shape = sta_passager_pos[i][j];
			std::pair<int, int> offset = GetPassagerOffset(j, j);
			std::vector<int> v = GetShapePoint(ptr_map->sta_appear[i].first + offset.first,
				ptr_map->sta_appear[i].second + offset.second,
				shape, 1);
			if (shape == 3 || shape == 4) {
				setfillcolor(BLACK);
				Graphics::DrawGraphics(shape * 2, v);
			}
			else {
				setlinecolor(BLACK);
				setfillcolor(BLACK);
				Graphics::DrawGraphics(shape * 2 + 1, v);
			}
		}
	}
	/*for (auto i : sta_passager_pos) {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "Here");
		for (auto j : i) {
			LOG4CPLUS_DEBUG(myLoger->rootLog, "sta_passager_pos has passagers" );
			
			LOG4CPLUS_DEBUG(myLoger->rootLog, "offset.first is" << offset.first);

			LOG4CPLUS_DEBUG(myLoger->rootLog, "offset.first is" << offset.first);
			
			if (j.shape == 3 || j.shape == 4) {
				setfillcolor(BLACK);
				Graphics::DrawGraphics(j.shape * 2, j.v_point);
			}
			else {
				setlinecolor(BLACK);
				setfillcolor(BLACK);
				Graphics::DrawGraphics(j.shape * 2 + 1, j.v_point);
			}
		}
		
	}*/
	LOG4CPLUS_DEBUG(myLoger->rootLog, "!Here");
}

void Station::DrawEndPicture() { 
	cleardevice();
	
	//mu_draw.lock();
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	settextstyle(40, 0, _T("黑体"));
	TCHAR s[] = _T("游戏结束");
	outtextxy(x - 400, 200, s);

	FlushBatchDraw();
	while(true) {
		
	}
	//mu_draw.unlock();
	cleardevice();
}

void Station::MonitorStationOvertime() {
	bool flag = false;
	while (true) {
		int i = 0;
		mu_warning.lock();
		while (sta_overtime.size()) {
			if (i == sta_overtime.size()) {
				i = 0;
			}
			int sta_num = sta_overtime[i].first;
			if (sta_passager_pos[sta_num].size() < 8) {
				CanclePassagerWarning(sta_num);
				//从sta_overtime中删除
				sta_overtime.erase(sta_overtime.begin() + i);
				LOG4CPLUS_ERROR(myLoger->rootLog, "after erase size " << sta_overtime.size());
				LOG4CPLUS_ERROR(myLoger->rootLog, "sta_passager_pos size " << sta_passager_pos[sta_num].size());
			}
			else {
				int t = time(NULL);
			//	LOG4CPLUS_ERROR(myLoger->rootLog, "t " << t << " " << sta_overtime[i].second);
				GetWarningInfo(sta_num, t - sta_overtime[i].second);
			
				if (t - sta_overtime[i].second == 60) {
					LOG4CPLUS_ERROR(myLoger->rootLog, "start change image...");
					gameover = true;

					flag = true;
					LOG4CPLUS_DEBUG(myLoger->rootLog, "change image end...");
					break;
				}
				i++;
			}
			if (sta_overtime.size() == 0) break;
			if (end) return;
		}
		mu_warning.unlock();
		if (flag) break;
		if (end) return;
	}
}