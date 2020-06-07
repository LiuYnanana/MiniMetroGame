#include "StartGame.h"

StartGame::StartGame()
{

}

void StartGame::DrawStartGame()
{
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(55, 0, _T("黑体"));

	TCHAR s[] = _T("模拟地铁游戏");
	outtextxy(330, 150, s);

	setlinecolor(BLACK);

	rectangle(380, 320, 420, 340);
	line(420, 310, 420, 350);
	line(420, 310, 445, 330);
	line(420, 350, 445, 330);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s1[] = _T("开始游戏");
	outtextxy(470, 315, s1);


	setlinecolor(BLACK);

	rectangle(380, 410, 420, 430);
	line(420, 400, 420, 440);
	line(420, 400, 445, 420);
	line(420, 440, 445, 420);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));

	TCHAR s2[] = _T("排行榜");
	outtextxy(470, 405, s2);

}

bool StartGame::JudgeStart(int x, int y)
{
	if (x >= 470 && x <= 595 && y >= 310 && y <= 345)
		return true;
	return false;
}

bool StartGame::JudgeEnd(int x, int y)
{
	if (x >= 470 && x <= 595 && y >= 400 && y <= 435)
		return true;
	return false;
}

bool StartGame::GetSelectGame()
{
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true) {
				if (JudgeStart(m.x, m.y)) {
					return true;
				}
				else if (JudgeEnd(m.x, m.y)) {
					return false;
				}
			}
		}
	}
}

StartGame::~StartGame()
{

}
