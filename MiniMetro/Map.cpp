#include "Map.h"

Map::Map() {}
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
}

void Map::DrawBackground() {
	initgraph(x + add_left + add_right, y);	// 创建绘图窗口，大小为 640x480 像素
	loadimage(NULL, background_path);
}

void Map::DrawRiver(std::string river_path) { 
	GetRiver(river_path);
	std::cout << river.size() << std::endl;
	for (auto i : river) {
		setfillcolor(RGB(174, 220, 252));
		solidcircle(i.first, i.second, 1);
	}
}

void Map::SetStationShapeNum() {
	num_pentagram = 2; //一个椭圆
	num_fivangle = 1; //两个五边形
	num_crisscross = 2; //两个扇形
	num_ractangle = 2; //两个正方形
	num_circle = station.size() * 2 / 5;
	num_triangle = station.size() - (num_pentagram + num_fivangle + num_crisscross + num_ractangle + num_circle);
	num_shape[3] = num_pentagram;
	num_shape[5] = num_fivangle;
	num_shape[4] = num_crisscross;
	num_shape[0] = num_ractangle;
	num_shape[1] = num_circle;
	num_shape[2] = num_triangle;
}

void Map::DrawStationShape(std::pair<int, int> pos) {
	srand(time(NULL));
	int k;
	std::cout << cnt_appear_sta << std::endl;
	if (cnt_appear_sta < 3) {
		do {
			k = rand() % 3;
			std::cout << k << std::endl;
		} while (vis_station_shape[k] == true);
		
		vis_station_shape[k] = true;
	}
	else if (cnt_appear_sta <= station.size() / 3) {
		do {
			k = rand() % 3 ;
			std::cout << k << " " << num_shape[k] << std::endl;
		} while (num_shape[k] == 0);
	}
	else {
		do {
			k = rand() % 6;
			std::cout << k << std::endl;
		} while (num_shape[k] == 0);
	}

	setlinecolor(BLACK);
	setfillcolor(WHITE);
	std::vector<int> v;
	int x = pos.first, y = pos.second;
	if (k == 0) {  //矩形
		v.push_back(x - 6);
		v.push_back(y - 6);
		v.push_back(x + 6);
		v.push_back(y + 6);
	}
	else if (k == 1) {  //圆
		v.push_back(x);
		v.push_back(y);
		v.push_back(6);
	}
	else if (k == 2) { //三角形
		v.push_back(x);
		v.push_back(y - 8);

		v.push_back(x - 6);
		v.push_back(y + 4);

		v.push_back(x + 6);
		v.push_back(y + 4);
	}
	else if (k == 3) { //五角星
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

	}
	else if (k == 4) { //120 53 十字形
		v.push_back(x - 6);
		v.push_back(y - 2);
		v.push_back(x + 6);
		v.push_back(y + 2);
		
		v.push_back(x - 2);
		v.push_back(y - 6);
		v.push_back(x + 2);
		v.push_back(y + 6);
	}
	else if (k == 5) { //五边形
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

	}
	Graphics::DrawGraphics(k * 2 + 1, v);
	num_shape[k]--;
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
	
		std::cout << "将第" << i << "个地铁站画在地图中" << std::endl;

		mu_draw.lock();
		DrawStationShape(sta_wait[i]);
		mu_draw.unlock();

		cnt_appear_sta++;
		sta_appear.push_back(sta_wait[i]);
		sta_wait.erase(sta_wait.begin() + i);
		
		
		int k = TimeInterval();
		std::cout << k << std::endl;
		Sleep(k * 10);
	}

}


void Map::DrawMap(std::string river_path, std::string station_path) {
	DrawBackground();
	DrawRiver(river_path);
}


