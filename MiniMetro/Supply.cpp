#include "Supply.h"

Supply::Supply(SubwayHead* _subwayHead, Bridge* _bridge, Track* _track, Clock* _clock, Map* _map) {
	ptr_sub_head = _subwayHead;
	ptr_bridge = _bridge;
	ptr_track = _track;
	ptr_clock = _clock;
	ptr_map = _map;
	myLoger = MyLogger::GetInstance();
}

int Supply::GetSelectSupply(int mx, int my) {
	for (auto i : supply_info) {
		int x = i.second.first, y = i.second.second;
		if ((mx - x) * (mx - x) + (my - y) * (my - y) <= 35 * 35) {
			return i.first;
		}
	}
	return 0;
}

void Supply::DealSelectSupply() {
	while (true) {
		//ptr_map->mu_mouse.lock();
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				int p = GetSelectSupply(m.x, m.y);
				LOG4CPLUS_DEBUG(myLoger->rootLog, "supply mouse" << m.x << " " << m.y);
				if (p) {
					if (p == 1) {
						ptr_sub_head->owned_sub_head++;
						LOG4CPLUS_DEBUG(myLoger->rootLog, "supply mouse" << ptr_sub_head->owned_sub_head);
					}
					else if (p == 2) {
						ptr_bridge->owned_bridge++;
					}
					else if (p == 3) {
						ptr_track->owned_track++;
					}
					else if (p == 4) {
						ptr_sub_head->sub_hold_passager += 2;
					}
					break;
				}
			}
		}
		//ptr_map->mu_mouse.unlock();
		if (end) return;
		
	}
	LOG4CPLUS_ERROR(myLoger->rootLog, "供应模块结束");
}

void Supply::DrawGovernmentSupply() {
	GetGovernmentSupply();
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(55, 0, _T("黑体"));

	TCHAR s[] = _T("请求下列补给中选择一个：");
	outtextxy(200, 150, s);

	for (auto i : supply_info) {
		int type = i.first, x = i.second.first, y = i.second.second;
		if (type == 1) {
			ptr_sub_head->DrawOneSubwayHead(x, y);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("黑体"));
			TCHAR s[] = _T("增加一列地铁");
			outtextxy(x - 60, y + 70, s);
		}
		else if (type == 2) {
			ptr_bridge->DrawOneBridge(x, y);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("黑体"));
			TCHAR s[] = _T("增加一个拱桥");
			outtextxy(x - 60, y + 70, s);
		}
		else if (type == 3) {
			ptr_track->DrawOneTrack(x, y);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("黑体"));
			TCHAR s[] = _T("增加一条线路");
			outtextxy(x - 60, y + 70, s);
		}
		else if (type == 4) {
			ptr_sub_head->DrawOneSubwayHead(x, y);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("黑体"));
			TCHAR s[] = _T("扩大地铁容量");
			outtextxy(x - 60, y + 70, s);
		}
	}
	FlushBatchDraw();
	DealSelectSupply();
}

void Supply::GetGovernmentSupply() {
	int day = ptr_clock->days;
	int week = day / 2 / 7;

	int cnt = 0;

	supply_info.clear();
	if (ptr_track->owned_track < 7) cnt++;
	if (ptr_bridge->owned_bridge < 7) cnt++;
	if (ptr_sub_head->owned_sub_head < 12) cnt++;
	if (ptr_sub_head->sub_hold_passager < 7) cnt++;
	
	if (cnt == 4) {
		supply_info.push_back(std::make_pair(1, std::make_pair(200, 350)));
		supply_info.push_back(std::make_pair(2, std::make_pair(400, 350)));
		supply_info.push_back(std::make_pair(3, std::make_pair(600, 350)));
		supply_info.push_back(std::make_pair(4, std::make_pair(800, 350)));
	}
	else if (cnt == 3) {
		int x = 305, y = 350;
		if (ptr_sub_head->owned_sub_head < 12) {
			supply_info.push_back(std::make_pair(1, std::make_pair(x, y)));
			x += 200;
		}
		if (ptr_track->owned_track < 7) {
			supply_info.push_back(std::make_pair(3, std::make_pair(x, y)));
			x += 200;
		}

		if (ptr_bridge->owned_bridge < 7) {
			supply_info.push_back(std::make_pair(2, std::make_pair(x, y)));
			x += 200;
		}
		if (ptr_sub_head->sub_hold_passager < 7) {
			supply_info.push_back(std::make_pair(4, std::make_pair(x, y)));
			x += 200;
		}
	}
	else if (cnt == 2) {
		int x = 376, y = 350;
		if (ptr_sub_head->owned_sub_head < 12) {
			supply_info.push_back(std::make_pair(1, std::make_pair(x, y)));
			x += 200;
		}
		if (ptr_track->owned_track < 7) {
			supply_info.push_back(std::make_pair(3, std::make_pair(x, y)));
			x += 200;
		}

		if (ptr_bridge->owned_bridge < 7) {
			supply_info.push_back(std::make_pair(2, std::make_pair(x, y)));
			x += 200;
		}
		if (ptr_sub_head->sub_hold_passager < 7) {
			supply_info.push_back(std::make_pair(4, std::make_pair(x, y)));
			x += 200;
		}
	}
	else if (cnt == 1) {
		int x = 490, y = 350;
		if (ptr_sub_head->owned_sub_head < 12) {
			supply_info.push_back(std::make_pair(1, std::make_pair(x, y)));
		}
		if (ptr_track->owned_track < 7) {
			supply_info.push_back(std::make_pair(3, std::make_pair(x, y)));
		}

		if (ptr_bridge->owned_bridge < 7) {
			supply_info.push_back(std::make_pair(2, std::make_pair(x, y)));
		}
		if (ptr_sub_head->sub_hold_passager < 7) {
			supply_info.push_back(std::make_pair(4, std::make_pair(x, y)));
		}
	}

}
Supply::~Supply()
{
}
