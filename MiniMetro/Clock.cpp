#include "Clock.h"

Clock::Clock() {}

void Clock::DrawDate(bool IsDay) {
	TCHAR s[5];
	int _d = days;
	if (!IsDay) _d--;
	if ((_d / 2) % 7 == 0) {
		_tcscpy(s, L"周一");
	}
	else if ((_d / 2) % 7 == 1) {
		_tcscpy(s, L"周二");
	}
	else if ((_d / 2) % 7 == 2) {
		_tcscpy(s, L"周三");
	}
	else if ((_d / 2) % 7 == 3) {
		_tcscpy(s, L"周四");
	}
	else if ((_d / 2) % 7 == 4) {
		_tcscpy(s, L"周五");
	}
	else if ((_d / 2) % 7 == 5) {
		_tcscpy(s, L"周六");
	}
	else if ((_d / 2) % 7 == 6) {
		_tcscpy(s, L"周日");
	}
	if (IsDay)
		settextcolor(BLACK);
	else settextcolor(RGB(244, 242, 238));
	setbkmode(TRANSPARENT);
	settextstyle(18, 0, _T("黑体"));
	outtextxy(x - 28 - 37, 70 - 25, s);
}

void Clock::DrawClockBackground() {
	if (days & 1) { //黑夜
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, y, r);
		setfillcolor(WHITE);
		solidcircle(x, y, 2);
	}
	else {
		setcolor(BLACK);
		setfillcolor(WHITE);
		fillcircle(x, y, r);
		setfillcolor(BLACK);
		solidcircle(x, y, 2);
	}
	if(days % 2 == 0) //新的一天开始
		DrawDate(false);
	DrawDate(true);
	
	
}

void Clock::DrawClockScale() {
	if (days & 1)
		setcolor(WHITE);
	else
		setcolor(BLACK);
	for (int i = 1; i <= 60; i++) {
		int x1 = static_cast<int>(x + (cos(i * (PI / 30))) * r);
		int y1 = static_cast<int>(y - (sin(i * (PI / 30))) * r);
		int x2, y2;
		if (i % 5 == 0)
		{
			x2 = static_cast<int>(x + (cos(i * (PI / 30))) * (r - 10));
			y2 = static_cast<int>(y - (sin(i * (PI / 30))) * (r - 10));
		}
		else
		{
			x2 = static_cast<int>(x + (cos(i * (PI / 30))) * (r - 5));
			y2 = static_cast<int>(y - (sin(i * (PI / 30))) * (r - 5));
		}
		line(x1, y1, x2, y2);
		
	}
}

void Clock::DrawClockPointer() {
	while (true) {
		mu_draw.lock();
		std::cout << "clock start!" << std::endl;
		DrawClockBackground();
		DrawClockScale();
		mu_draw.unlock();

		for (int i = 1; i <= 60; i++) {
			int x2 = static_cast<int>(x - (sin(i * (PI / 30))) * (r - 20));
			int y2 = static_cast<int>(y + (cos(i * (PI / 30))) * (r - 20));

			//double t = cos(i * (PI / 30));
			//std::cout << x2 << ' ' << y2 << ' ' << t << std::endl;
			mu_draw.lock();
			if (days & 1) {
				setcolor(WHITE);
				line(x, y, x2, y2);
			}
			else {
				setcolor(BLACK);
				line(x, y, x2, y2);
			}
			mu_draw.unlock();

			Sleep(10000 / 60);

			mu_draw.lock();
			if (days & 1) {
				setcolor(BLACK);
				line(x, y, x2, y2);
			}
			else {
				setcolor(WHITE);
				line(x, y, x2, y2);
			}
			mu_draw.unlock();
		}
		days++;
		std::cout << "clock end!" << std::endl;
	}
}

Clock::~Clock() {}
