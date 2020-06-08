#include "City.h"

City::City()
{
}

void City::DrawRankCity()
{
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(55, 0, _T("黑体"));

	TCHAR s[] = _T("选择城市");
	outtextxy(375, 150, s);

	circle(340, 300, 50);
	circle(500, 300, 50);
	circle(660, 300, 50);

	circle(280, 450, 50);
	circle(415, 450, 50);
	circle(585, 450, 50);
	circle(720, 450, 50);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s1[] = _T("北京");
	outtextxy(310, 285, s1);

	TCHAR s2[] = _T("上海");
	outtextxy(470, 285, s2);

	TCHAR s3[] = _T("杭州");
	outtextxy(630, 285, s3);

	TCHAR s4[] = _T("深圳");
	outtextxy(250, 435, s4);

	TCHAR s5[] = _T("天津");
	outtextxy(385, 435, s5);

	TCHAR s6[] = _T("重庆");
	outtextxy(555, 435, s6);

	TCHAR s7[] = _T("成都");
	outtextxy(690, 435, s7);

	/*setlinecolor(BLACK);

	rectangle(390, 295, 430, 315);
	line(430, 285, 430, 325);
	line(430, 285, 455, 305);
	line(430, 325, 455, 305);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s1[] = _T("北京");
	outtextxy(480, 290, s1);*/



	
	/*setlinecolor(BLACK);

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
	outtextxy(480, 515, s4);*/
}

void City::DrawEasyCity()
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

	TCHAR s1[] = _T("成都");
	outtextxy(480, 290, s1);

	setlinecolor(BLACK);

	rectangle(390, 370, 430, 390);
	line(430, 360, 430, 400);
	line(430, 360, 455, 380);
	line(430, 400, 455, 380);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s2[] = _T("重庆");
	outtextxy(480, 365, s2);
}

void City::DrawMidCity()
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

	TCHAR s2[] = _T("深圳");
	outtextxy(480, 365, s2);

	rectangle(390, 445, 430, 465);
	line(430, 435, 430, 475);
	line(430, 435, 455, 455);
	line(430, 475, 455, 455);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s3[] = _T("天津");
	outtextxy(480, 440, s3);
}

void City::DrawHardCity()
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

	TCHAR s1[] = _T("杭州");
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
}

std::string City::SelectRankCity()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
			
				if ((m.x - 340) * (m.x - 340) + (m.y - 300) * (m.y - 300) <= 50 * 50) {
					return "Beijing";
				}
				else if ((m.x - 500) * (m.x - 500) + (m.y - 300) * (m.y - 300) <= 50 * 50) {
					return "ShangHai";
				}
				else if ((m.x - 660) * (m.x - 660) + (m.y - 300) * (m.y - 300) <= 50 * 50) {
					return "HangZhou";
				}
				else if ((m.x - 280) * (m.x - 280) + (m.y - 450) * (m.y - 450) <= 50 * 50) {
					return "ShenZhen";
				}
				else if ((m.x - 415) * (m.x - 415) + (m.y - 450) * (m.y - 450) <= 50 * 50) {
					return "TianJin";
				}
				else if ((m.x - 585) * (m.x - 585) + (m.y - 450) * (m.y - 450) <= 50 * 50) {
					return "ChongQing";
				}
				else if ((m.x - 720) * (m.x - 720) + (m.y - 450) * (m.y - 450) <= 50 * 50) {
					return "ChengDu";
				}
			}
		}
	}
	return 0;
}

std::string City::SelectEasyCity()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (m.x >= 480 && m.x <= 540 && m.y >= 290 && m.y <= 320) {
					return "ChengDu";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 365 && m.y <= 395) {
					return "ChongQing";
				}
			}
		}
	}
}

std::string City::SelectMidCity()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (m.x >= 480 && m.x <= 540 && m.y >= 290 && m.y <= 320) {
					return "Beijing";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 365 && m.y <= 395) {
					return "ShenZhen";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 440 && m.y <= 470) {
					return "TianJin";
				}
			}
		}
	}
}

std::string City::SelectHardCity()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (m.x >= 480 && m.x <= 540 && m.y >= 290 && m.y <= 320) {
					return "HangZhou";
				}
				else if (m.x >= 480 && m.x <= 540 && m.y >= 365 && m.y <= 395) {
					return "ShangHai";
				}
			}
		}
	}
}

City::~City()
{
}
