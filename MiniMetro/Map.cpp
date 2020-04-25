#include "Map.h"

Map::Map() {
	myLoger = MyLogger::GetInstance();
}
Map::~Map() {}


void Map::GetStation(std::string station_path) {
	File station_file;
	std::vector<std::string> p; 
	station_file.ReadTxt(station_path, p);
	
	for(auto i : p) {
		int x, y;
		sscanf_s(i.c_str(), "(%d, %d)", &x, &y);
		int a = x * a1 / b1 + add_left;
		int b = y * a2 / b2;
		station.push_back(std::make_pair(a, b));  
	}
	LOG4CPLUS_INFO(myLoger->rootLog, "station number is " << station.size());
} 

void Map::GetRiver(std::string river_path) {
	File river_file;
	std::vector<std::string> p;
	river_file.ReadTxt(river_path, p);

	for (auto i : p) {
		int x, y;
		sscanf_s(i.c_str(), "(%d, %d)", &x, &y);
		int a = x * a2 / b2;
		int b = y * a1 / b1 + add_left;
		river.push_back(std::make_pair(b, a));
	}
	LOG4CPLUS_INFO(myLoger->rootLog, "map river'points number is " << river.size());
}


bool Map::cmp_distance_center(std::pair<int, int> a, std::pair<int, int> b) {
	int dist1 = (a.first - cx) * (a.first - cx) + (a.second - cy) * (a.second - cy);
	int dist2 = (b.first - cx) * (b.first - cx) + (b.second - cy) * (b.second - cy);
	return dist1 < dist2;
}

bool Map::cmp_river_x(std::pair<int, int> a, std::pair<int, int> b) {
	return a.first > b.first;
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
			if (abs(station[j].first - station[i].first) < 40 && abs(station[j].second - station[i].second) < 40) {
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
	LOG4CPLUS_INFO(myLoger->rootLog, "after remove adjacent, station number is " << station.size());
}

void Map::DrawBackground() {
	LOG4CPLUS_INFO(myLoger->rootLog, "start init graph and load image");
	initgraph(x + add_left + add_right, y);	// ������ͼ���ڣ���СΪ 640x480 ����
	loadimage(NULL, background_path);
	LOG4CPLUS_INFO(myLoger->rootLog, "init graph and load image successed!");
}

void Map::DrawRiver(std::string river_path) { 
	GetRiver(river_path);
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw river");
	for (auto i : river) {
		setfillcolor(RGB(174, 220, 252));
		solidcircle(i.first, i.second, 1);
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "river is successfully drawn");
}

void Map::SetStationShapeNum() {
	num_pentagram = 2; //һ�������
	num_fivangle = 1; //���������
	num_crisscross = 2; //����ʮ����
	num_ractangle = 2; //����������
	num_circle = station.size() * 2 / 5;
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

	setlinecolor(BLACK);
	setfillcolor(WHITE);
	std::vector<int> v;
	int x = pos.first, y = pos.second;
	if (k == 0) {  //����
		v.push_back(x - 6);
		v.push_back(y - 6);
		v.push_back(x + 6);
		v.push_back(y + 6);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is ractangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(left-top, right-bottom): (" 
			<< x - 6 << ", "<< y - 6 << "), (" 
			<< x + 6 << ", " << y + 6 << ")" );
	}
	else if (k == 1) {  //Բ
		v.push_back(x);
		v.push_back(y);
		v.push_back(6);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is circle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate(circle-center, radius): ("
			<< x << ", " << y << "), 6");
	}
	else if (k == 2) { //������
		v.push_back(x);
		v.push_back(y - 8);

		v.push_back(x - 6);
		v.push_back(y + 4);

		v.push_back(x + 6);
		v.push_back(y + 4);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is triangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y + 4 << "), ("
		    << x + 6 << ", " << y + 4 << ")");
	}
	else if (k == 3) { //�����
		v.push_back(x);
		v.push_back(y - 8);

		v.push_back(x - 6);
		v.push_back(y + 4);

		v.push_back(x + 6);
		v.push_back(y + 4);

		v.push_back(x - 6);
		v.push_back(y - 4);

		v.push_back(x);
		v.push_back(y + 8);

		v.push_back(x + 6);
		v.push_back(y - 4);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is pentagram");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y + 4 << "), ("
			<< x + 6 << ", " << y + 4 << "), ("
			<< x - 6 << ", " << y - 4 << "), ("
			<< x << ", " << y + 8 << "), ("
			<< x + 6 << ", " << y - 4 << ")");
	}
	else if (k == 4) { //120 53 ʮ����
		v.push_back(x - 6);
		v.push_back(y - 2);
		v.push_back(x + 6);
		v.push_back(y + 2);
		
		v.push_back(x - 2);
		v.push_back(y - 6);
		v.push_back(x + 2);
		v.push_back(y + 6);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is crisscross");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x + 6 << ", " << y + 2 << "), ("
			<< x - 2<< ", " << y - 6 << "), ("
			<< x + 2 << ", " << y + 6 << ")");
	}
	else if (k == 5) { //�����
		v.push_back(x);
		v.push_back(y - 8);

		v.push_back(x - 6);
		v.push_back(y - 2);

		v.push_back(x - 4);
		v.push_back(y + 6);

		v.push_back(x + 4);
		v.push_back(y + 6);

		v.push_back(x + 6);
		v.push_back(y - 2);

		LOG4CPLUS_DEBUG(myLoger->rootLog, "this shape is fivangle");
		LOG4CPLUS_DEBUG(myLoger->rootLog, "coordinate: ("
			<< x << ", " << y - 8 << "), ("
			<< x - 6 << ", " << y - 2 << "), ("
			<< x - 4 << ", " << y + 6 << "), ("
			<< x - 6 << ", " << y - 4 << "), ("
			<< x + 4 << ", " << y + 6 << "), ("
			<< x + 6 << ", " << y - 2 << ")");
	}
	Graphics::DrawGraphics(k * 2 + 1, v);
	num_shape[k]--;
	LOG4CPLUS_DEBUG(myLoger->rootLog, "the " << k << " shape left " << num_shape[k]);
	v_station_shape.push_back(k);

}

void Map::DrawStation(std::string station_path) {
	GetStation(station_path);
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

		mu_draw.lock();
		DrawStationShape(sta_wait[i]);
		mu_draw.unlock();

		cnt_appear_sta++;
		LOG4CPLUS_DEBUG(myLoger->rootLog, "appeared station number is " << cnt_appear_sta);
		sta_appear.push_back(sta_wait[i]);
		sta_wait.erase(sta_wait.begin() + i);
		
		
		int k = TimeInterval();
		LOG4CPLUS_INFO(myLoger->rootLog, "station appear time Interval is " << k << "ms");
		Sleep(k * 10);
	}

}


void Map::DrawMap(std::string river_path, std::string station_path) {
	DrawBackground();
	DrawRiver(river_path);
}

