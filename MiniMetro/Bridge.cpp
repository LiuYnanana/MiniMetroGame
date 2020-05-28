#include "Bridge.h"

Bridge::Bridge() {
	myLoger = MyLogger::GetInstance();
	owned_bridge = 3;
	used_bridge = 0;
	have_bridge = true;
}

void Bridge::GetBridgeInfo() {
	bridge_info.clear();
	int x = 40, y = 480;
	for (int i = 0; i < owned_bridge - used_bridge; i++) {
		bridge_info.push_back(std::make_pair(x, y));
		x += 15;
	}
}

void Bridge::DrawNoBridge() {
	if (!have_bridge) {
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("黑体"));

		TCHAR s[] = _T("无可用桥梁");
		outtextxy(20, 480, s);
	}

	
}

void Bridge::DrawOneBridge(int x, int y) {
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillcircle(x, y, r);     //  40 480
	line(x - 22, y - 14, x + 22, y - 14);
	line(x - 22, y - 14, x - 22, y + 13);
	line(x + 22, y - 14, x + 22, y + 13);
	line(x - 22, y - 16, x + 22, y - 16);
	fillpie(x - 14, y - 9, x + 14, y + 31, 0, 66);
	setlinecolor(WHITE);
	line(x - 14, y + 12, x + 14, y + 12);
	line(x - 14, y + 11, x + 14, y + 11);
	setcolor(BLACK);
	fillcircle(x - 18, y + 3, 2);
	fillcircle(x - 14, y - 6, 3);
	fillcircle(x + 18, y + 3, 2);
	fillcircle(x + 14, y - 6, 3);
	setlinecolor(BLACK);
	line(x - 22, y - 14, x - 22, y - 19);
	line(x + 22, y - 14, x + 22, y - 19);
	line(x - 11, y - 14, x - 11, y - 19);// 40 480
	line(x + 11, y - 14, x + 11, y - 19);
	line(x, y - 14, x, y - 19);
}

void Bridge::DrawBridge() {
	GetBridgeInfo();
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw bridge");
	if (bridge_info.size() == 0) have_bridge = false;
	DrawNoBridge();
	for (auto i : bridge_info) {
		int x = i.first, y = i.second;
		DrawOneBridge(x, y);
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "bridge is successfully drawn");
}

Bridge::~Bridge() {}