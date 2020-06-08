#include "Mode.h"

Mode::Mode()
{
}

void Mode::DrawMode()
{
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(55, 0, _T("黑体"));

	TCHAR s[] = _T("模式选择");
	outtextxy(375, 150, s);
   
	setlinecolor(BLACK);

	rectangle(390, 295, 430, 315);
	line(430, 285, 430, 325);
	line(430, 285, 455, 305);
	line(430, 325, 455, 305);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s1[] = _T("简单");
	outtextxy(480, 290, s1);

	setlinecolor(BLACK);

	rectangle(390, 370, 430, 390);
	line(430, 360, 430, 400);
	line(430, 360, 455, 380);
	line(430, 400, 455, 380);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s2[] = _T("中等");
	outtextxy(480, 365, s2);

	rectangle(390, 445, 430, 465);
	line(430, 435, 430, 475);
	line(430, 435, 455, 455);
	line(430, 475, 455, 455);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s3[] = _T("困难");
	outtextxy(480, 440, s3);
}

int Mode::SelectMode()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (m.x >= 480 && m.x <= 540 && m.y >= 290 && m.y <= 320) {
					return 0;
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 365 && m.y <= 395) {
					return 1;
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 440 && m.y <= 470) {
					return 2;
				}
			}
		}
	}

}

Mode::~Mode()
{
}
