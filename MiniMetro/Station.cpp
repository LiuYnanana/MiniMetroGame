#include "Station.h"

Station::Station(Map *mp){
	ptr_map = mp;
	sta_passager_pos.resize(100);
}

Station::~Station(){}

int Station::RandPassagerTime() { 
	srand(time(NULL));
	int k = sqrt(rand() % 100);
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

void Station::DrawPassagerWarning(int k) {
	int x = ptr_map->sta_appear[k].first;
	int y = ptr_map->sta_appear[k].second;

	double PI = acos(-1);
	for (int i = 1; i <= 60; i++) {

		mu_draw.lock();
		int x2 = static_cast<int>(x + (sin(i * (PI / 30))) * 4);
		int y2 = static_cast<int>(y - (cos(i * (PI / 30))) * 4);

		setlinecolor(RED);
		line(x, y, x2, y2);
		mu_draw.unlock();

		Sleep(20000 / 60);
	}

}

void Station::CanclePassagerWarning(int k) {
	int x = ptr_map->sta_appear[k].first;
	int y = ptr_map->sta_appear[k].second;

	int shape = ptr_map->v_station_shape[k];

	mu_draw.lock();
	DrawShape(x, y, shape);

	mu_draw.unlock();


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
		
		do {
			sta_num = rand() % ptr_map->sta_appear.size(); //确定给哪个站点增加新乘客
			LOG4CPLUS_DEBUG(myLoger->rootLog, "the passager at " << sta_num << "station");
		} while (find_if(sta_overtime.begin(), sta_overtime.end(), [
			sta_num](const std::pair<int, int> a) {return a.first == sta_num; }) != sta_overtime.end());


		LOG4CPLUS_DEBUG(myLoger->rootLog, "finally the passager at " << sta_num << "station");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_shape have:");

		LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_num start rand...");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "v_station_shape[sta_num] is " << ptr_map->v_station_shape[sta_num]);
		
		int shape_num;
		do{                               
			shape_num = rand() % ptr_map->v_station_shape.size(); //确定增加什么类型的乘客
			LOG4CPLUS_DEBUG(myLoger->rootLog, "the shape_num is " << shape_num);
		} while (ptr_map->v_station_shape[shape_num] == ptr_map->v_station_shape[sta_num]);
		
		mu_station.lock();
		std::pair<int, int> offset = GetPassagerOffset(sta_num, -1);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "offset.first is" << offset.first);
		
	

		LOG4CPLUS_DEBUG(myLoger->rootLog, "offset.first is" << offset.first);
		std::vector<int> v = GetShapePoint(ptr_map->sta_appear[sta_num].first + offset.first,
			ptr_map->sta_appear[sta_num].second + offset.second,
			ptr_map->v_station_shape[shape_num], 1);

		

		passager_shape t_struct;
		t_struct.shape = ptr_map->v_station_shape[shape_num];
		t_struct.v_point = v;
		sta_passager_pos[sta_num].push_back(t_struct);

		mu_station.unlock();
		if (sta_passager_pos[sta_num].size() == 8) { //車站到達最大承載量
			sta_overtime.push_back(std::make_pair(sta_num, time(NULL)));
		//	DrawPassagerWarning(sta_num);
		}
		int t = RandPassagerTime();
		LOG4CPLUS_DEBUG(myLoger->rootLog, "passager appear time " << t);
		Sleep(t * 1000);
	}

}

void Station::DrawStationPassager() {
	for (auto i : sta_passager_pos) {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "Here");
		for (auto j : i) {
			LOG4CPLUS_DEBUG(myLoger->rootLog, "sta_passager_pos has passagers" );
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
		
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "!Here");
}

void Station::DrawEndPicture() { 
	cleardevice();

	mu_draw.lock();
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	settextstyle(30, 0, _T("黑体"));
	TCHAR s[] = _T("游戏结束");
	outtextxy(x - 400, 200, s);

	mu_draw.unlock();
}

void Station::MonitorStationOvertime() {
	bool flag = false;
	while (true) {
		int i = 0;
		while (sta_overtime.size()) {
			if (i == sta_overtime.size()) {
				i = 0;
			}

			int t = time(NULL);
			if (t - sta_overtime[i].second == 100) {
				LOG4CPLUS_DEBUG(myLoger->rootLog, "start change image...");
				//IMAGE img;
				//getimage(&img, 0, 0, x + 200, y);
				DrawEndPicture();
				flag = true;
				LOG4CPLUS_DEBUG(myLoger->rootLog, "change image end...");
				break;
			}
			i++;
		}
		if (flag) break;
	}
}