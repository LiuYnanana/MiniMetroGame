#include "Map.h"

Map::Map() {
	myLoger = MyLogger::GetInstance();
}
Map::Map(std::string _river, std::string _station, std::string _place){
	myLoger = MyLogger::GetInstance();
	river_path = _river;
	station_path = _station;
	place = _place;
}

//Map::Map(Map& mp) {
//	myLoger = MyLogger::GetInstance();
//	sta_appear = mp.sta_appear;
//	v_station_shape = mp.v_station_shape;
//}
Map::~Map() {}


void Map::GetStation() {
	//File station_file;
	std::vector<std::string> p; 
	Redis redis_station;
	redis_station.connect("127.0.0.1", 6379);
	p = redis_station.GetList(place + "_station");
	//station_file.ReadTxt(station_path, p);
	
	for(auto i : p) {
		int x, y;
		sscanf_s(i.c_str(), "(%d, %d)", &x, &y);
		x = x / 2;
		y = y * 3 / 5;
		int a = x * a1 / b1 + add_left;
		int b = y * a2 / b2;
		station.push_back(std::make_pair(a, b));  
	}
	LOG4CPLUS_INFO(myLoger->rootLog, "station number is " << station.size());
} 
bool Map::cmp_river_x(std::pair<int, int> a, std::pair<int, int> b) {
	if(a.first != b.first) return a.first < b.first;
	return a.second < b.second;
}

void Map::RemoveAdjacentRiver() {
	sort(river.begin(), river.end(), cmp_river_x);
	point_list t;
	t.push_back(river[0]);
	for (int i = 1; i < river.size(); i++) {
		int len = t.size() - 1;
		if (abs(river[i].first - t[len].first) <= 3 && abs(river[i].second - t[len].second) <= 3)
			continue;
		t.push_back(river[i]);
	}
	river.clear();
	for (auto i : t) {
		river.push_back(i);
	//	LOG4CPLUS_ERROR(myLoger->rootLog, "river info " << i.first << " " << i.second);
	}

}

void Map::GetRiver() {
	//File river_file;
	std::vector<std::string> p;
	Redis redis_river;
	redis_river.connect("127.0.0.1", 6379);
	p = redis_river.GetList(place + "_river");
	//river_file.ReadTxt(river_path, p);
	mu_map_diver.lock();
	for (auto i : p) {
		int x, y;
		sscanf_s(i.c_str(), "(%d, %d)", &x, &y);
		x = x * 3 / 5;
		y = y / 2;
		int a = x * a2 / b2;
		int b = y * a1 / b1 + add_left;
		river.push_back(std::make_pair(b, a));
	}
	mu_map_diver.unlock();

	RemoveAdjacentRiver();
	LOG4CPLUS_ERROR(myLoger->rootLog, "map river'points number is " << river.size());
}


bool Map::cmp_distance_center(std::pair<int, int> a, std::pair<int, int> b) {
	int dist1 = (a.first - cx) * (a.first - cx) + (a.second - cy) * (a.second - cy);
	int dist2 = (b.first - cx) * (b.first - cx) + (b.second - cy) * (b.second - cy);
	return dist1 < dist2;
}

int Map::TimeInterval() {
	int len = station.size();
	srand(time(NULL));
	int k = rand() % len;
	int a = 14, b = 5, c = 1;
	int x1 = len * a / (a + b + c);
	int x2 = len * b / (a + b + c);

	int t = (rand() % 20) - 10;
	if (k < x1) return 30 + t;
	if (k < x2) return 60 + t;
	return 90 + t;
}

void Map::RemoveAdjacentPoint() {
	point_list t;
	int len = station.size();
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (abs(station[j].first - station[i].first) < 30 && abs(station[j].second - station[i].second) < 30) {
				for (int k = j + 1; k < len; k++) {
					station[k - 1] = station[k];
				}
				j--;
				len--;
			}
		}
		t.push_back(station[i]);
	}
	station.clear();

	for (auto i : t) {
		station.push_back(i);
	}
	LOG4CPLUS_ERROR(myLoger->rootLog, "after remove adjacent, station number is " << station.size());
}

void Map::DrawBackground() {
	LOG4CPLUS_INFO(myLoger->rootLog, "start init graph and load image");
	initgraph(1000, 644);	// 创建绘图窗口，大小为 640x480 像素
	//loadimage(NULL, background_path);
	
	setbkcolor(RGB(245, 243, 239));
	cleardevice();

	LOG4CPLUS_INFO(myLoger->rootLog, "init graph and load image successed!");
}

void Map::DrawRiver() { 
	//GetRiver(river_path);
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw river");
	mu_map_diver.lock();
	for (auto i : river) {
		setfillcolor(RGB(174, 220, 252));
		solidcircle(i.first, i.second, 2);
	}
	mu_map_diver.unlock();
	LOG4CPLUS_DEBUG(myLoger->rootLog, "river is successfully drawn");
}


void Map::SetStationShapeNum() {
	num_pentagram = station.size() * 1 / 15; //一个五角星
	num_fivangle = station.size() * 1 / 15; //两个五边形
	num_crisscross = station.size() * 1 / 15; //两个十字形
	num_ractangle = station.size() * 2 / 15; //两个正方形
	num_circle = station.size() * 5 / 15;
	num_triangle = station.size() - (num_pentagram + num_fivangle + num_crisscross + num_ractangle + num_circle);
	num_shape[3] = num_pentagram;
	num_shape[5] = num_fivangle;
	num_shape[4] = num_crisscross;
	num_shape[0] = num_ractangle;
	num_shape[1] = num_circle;
	num_shape[2] = num_triangle;

	LOG4CPLUS_INFO(myLoger->rootLog, "the number of pentagram is " << num_pentagram);
	LOG4CPLUS_INFO(myLoger->rootLog, "the number of fivangle is " << num_fivangle);
	LOG4CPLUS_INFO(myLoger->rootLog, "the number of crisscross is " << num_crisscross);
	LOG4CPLUS_INFO(myLoger->rootLog, "the number of ractangle is " << num_ractangle);
	LOG4CPLUS_INFO(myLoger->rootLog, "the number of circle is " << num_circle);
	LOG4CPLUS_INFO(myLoger->rootLog, "the number of triangle is " << num_triangle);
}

void Map::DrawShape(int x, int y, int k) {

	std::vector<int> v;
	if (k == 0) {  //矩形
		v.push_back(x - 6);
		v.push_back(y - 6);
		v.push_back(x + 6);
		v.push_back(y + 6);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is ractangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(left-top, right-bottom): ("
			<< x - 6 << ", " << y - 6 << "), ("
			<< x + 6 << ", " << y + 6 << ")");
	}
	else if (k == 1) {  //圆
		v.push_back(x);
		v.push_back(y);
		v.push_back(7);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is circle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(circle-center, radius): ("
			<< x << ", " << y << "), 6");
	}
	else if (k == 2) { //三角形
		v.push_back(x);
		v.push_back(y - 9);

		v.push_back(x - 7);
		v.push_back(y + 5);

		v.push_back(x + 7);
		v.push_back(y + 5);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is triangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y + 4 << "), ("
			<< x + 6 << ", " << y + 4 << ")");
	}
	else if (k == 3) { //五角星
		v.push_back(x);
		v.push_back(y - 9);

		v.push_back(x - 7);
		v.push_back(y + 5);

		v.push_back(x + 7);
		v.push_back(y + 5);

		v.push_back(x - 7);
		v.push_back(y - 5);

		v.push_back(x);
		v.push_back(y + 9);

		v.push_back(x + 7);
		v.push_back(y - 5);

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
		v.push_back(x - 7);
		v.push_back(y - 3);
		v.push_back(x + 7);
		v.push_back(y + 3);

		v.push_back(x - 3);
		v.push_back(y - 7);
		v.push_back(x + 3);
		v.push_back(y + 7);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is crisscross");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x + 6 << ", " << y + 2 << "), ("
			<< x - 2 << ", " << y - 6 << "), ("
			<< x + 2 << ", " << y + 6 << ")");
	}
	else if (k == 5) { //五边形
		v.push_back(x);
		v.push_back(y - 9);

		v.push_back(x - 7);
		v.push_back(y - 3);

		v.push_back(x - 5);
		v.push_back(y + 7);

		v.push_back(x + 5);
		v.push_back(y + 7);

		v.push_back(x + 7);
		v.push_back(y - 3);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is fivangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x - 4 << ", " << y + 6 << "), ("
			<< x - 6 << ", " << y - 4 << "), ("
			<< x + 4 << ", " << y + 6 << "), ("
			<< x + 6 << ", " << y - 2 << ")");
	}

	appear_sta_info.push_back(std::make_pair(k * 2 + 1, v));
}

void Map::DrawStationShape(std::pair<int, int> pos) {
	srand(time(NULL));
	int k;
	if (cnt_appear_sta < 3) {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this station is top three");
		do {
			k = rand() % 3;
			LOG4CPLUS_DEBUG(myLoger->rootLog, "shape is " << k);
		} while (vis_station_shape[k] == true);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "finally shape is " << k);
		vis_station_shape[k] = true;
	}
	else if (cnt_appear_sta <= station.size() / 3) {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this station is one third");
		do {
			k = rand() % 3 ;
			LOG4CPLUS_DEBUG(myLoger->rootLog, "shape is " << k);
		} while (num_shape[k] == 0);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "finally shape is " << k);
	}
	else {
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this station is at last");
		do {
			k = rand() % 6;
			LOG4CPLUS_DEBUG(myLoger->rootLog, "shape is " << k);
		} while (num_shape[k] == 0);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "finally shape is " << k);
	}

	int x = pos.first, y = pos.second;

	DrawShape(x, y, k);

	num_shape[k]--;
	LOG4CPLUS_DEBUG(myLoger->rootLog, "the " << k << " shape left " << num_shape[k]);
	v_station_shape.push_back(k);

}

void Map::GetStationInfo() {
	//GetStation();
	RemoveAdjacentPoint();
	SetStationShapeNum();
	for (auto i : station) {
		sta_wait.push_back(std::make_pair(i.first, i.second));
	}

	sort(sta_wait.begin(), sta_wait.end(), Map::cmp_distance_center);
	srand(time(NULL));
	while (cnt_appear_sta != station.size()) {

		int mod = min(sta_wait.size(), 3);
		int i = rand() % mod;
	
		LOG4CPLUS_DEBUG(myLoger->rootLog, "the " << i << " station will be draw..");

		DrawStationShape(sta_wait[i]);

		cnt_appear_sta++;
		LOG4CPLUS_DEBUG(myLoger->rootLog, "appeared station number is " << cnt_appear_sta);
		mu_map.lock();
		sta_appear.push_back(sta_wait[i]);
		sta_wait.erase(sta_wait.begin() + i);
		mu_map.unlock();
		
		int k = TimeInterval();
		if (cnt_appear_sta == 1) k = 0;
		LOG4CPLUS_INFO(myLoger->rootLog, "station appear time interval is " << k << "ms");
		
		if (end) return;
		Sleep(k * 100);
	}
	LOG4CPLUS_ERROR(myLoger->rootLog, "appear staton number is " << sta_appear.size());
}

void Map::DrawStation() {
	for (auto i : appear_sta_info) {
		setlinecolor(BLACK);
		setfillcolor(WHITE); 
		
		Graphics::DrawGraphics(i.first, i.second);
	}
	rectangle(15, 20, 35, 30);
	line(15, 15, 15, 35);
	line(15, 15, 5, 25);
	line(15, 35, 5, 25);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("黑体"));

	TCHAR s[] = _T("退出");
	outtextxy(40, 15, s);

//	line(10, 15, 80, 30);
}

void Map::DrawMap() {
	DrawBackground();
	DrawRiver();
}


