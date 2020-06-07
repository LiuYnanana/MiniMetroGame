#include "City.h"

City::City()
{
}

void City::DrawCity()
{
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(55, 0, _T("黑体"));

	TCHAR s[] = _T("选择城市");
	outtextxy(375, 150, s);

	setlinecolor(BLACK);

	rectangle(390, 295, 430, 315);
	line(430, 285, 430, 325);
	line(430, 285, 455, 305);
	line(430, 325, 455, 305);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s1[] = _T("北京");
	outtextxy(480, 290, s1);

	
	setlinecolor(BLACK);

	rectangle(390, 370, 430, 390);
	line(430, 360, 430, 400);
	line(430, 360, 455, 380);
	line(430, 400, 455, 380);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s2[] = _T("上海");
	outtextxy(480, 365, s2);

	rectangle(390, 445, 430, 465);
	line(430, 435, 430, 475);
	line(430, 435, 455, 455);
	line(430, 475, 455, 455);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s3[] = _T("杭州");
	outtextxy(480, 440, s3);

	rectangle(390, 520, 430, 540);
	line(430, 510, 430, 550);
	line(430, 510, 455, 530);
	line(430, 550, 455, 530);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s4[] = _T("深圳");
	outtextxy(480, 515, s4);
}

std::string City::SelectCity()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (m.x >= 480 && m.x <= 540 && m.y >= 290 && m.y <= 320) {
					return "Beijing";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 365 && m.y <= 395) {
					return "ShangHai";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 440 && m.y <= 470) {
					return "HangZhou";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 515 && m.y <= 545) {
					return "ShenZhen";
				}
			}
		}
	}
	return 0;
}

City::~City()
{
}
