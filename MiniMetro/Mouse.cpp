#include "Mouse.h"

Mouse::Mouse(Map* _map, Route* _route, SubwayHead* _sub, Supply* _supply)
{
	ptr_map = _map;
	ptr_route = _route;
	ptr_subway = _sub;
	ptr_supply = _supply;
}

bool Mouse::JudgeExit(MOUSEMSG m) {
	//line(10, 15, 80, 30);
	if (m.x >= 10 && m.x <= 80 && m.y >= 15 && m.y <= 30)
		return true;
	return false;
}

void Mouse::MonitorMouse()
{
	int sx = -1, sy = -1;
	int flag = -1;
	int t_route_id = -1;
	Rank rank;
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				ptr_route->GetRouteInfo(m, sx, sy, flag, t_route_id);
			}
			else if (m.uMsg == WM_LBUTTONUP) {
				ptr_route->GetRouteInfo(m, sx, sy, flag, t_route_id);
			}
			
			ptr_subway->GetSelectInfo(m);

			if(m.mkLButton == true && JudgeExit(m)) {
				end = true;
				SYSTEMTIME sys;
				GetLocalTime(&sys);
				std::string time = "";
				std::string t = std::to_string(sys.wYear);
				time = time + t;
				t = std::to_string(sys.wMonth);
				time = time + "/" + t;
				t = std::to_string(sys.wDay);
				time = time + "/" +t + "  ";
				t = std::to_string(sys.wHour);
				time = time + t;
				t = std::to_string(sys.wMinute);
				time = time + ":" + t;
				std::cout << ptr_map->place + "_rank" << std::endl;
				std::cout << time << std::endl;
				rank.SaveRank(ptr_map->place + "_rank", ptr_subway->people, time);
				return;
			}
		}
		Sleep(1);
	}
}

Mouse::~Mouse()
{
}
